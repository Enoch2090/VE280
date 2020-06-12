/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu. 
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */

#include "simulation.h"
using namespace std;
// TODO: Define your functions
/* Simulation Processing Functions */

void simulation(const char *userpath, const char *logpath)
{ // Main simulation function
    //------Read users------
    Server_t server;
    server.num_tags = 0;
    server.num_users = 0;
    try
    {
        serverInit(server, userpath);
    }
    catch (const Exception_t &exception)
    {
        throw exception;
    }
    try
    {
        readUserInfo(server);
    }
    catch (const Exception_t &exception)
    {
        throw exception;
    }
    // console(server);
    // refresh(server, "paul.weng");
    // cout << "+-+-+-+-+-+==========+-+-+-+-+-+" << endl;
    // follow(server, "paul.weng", "marstin");
    // refresh(server, "paul.weng");
    // cout << "+-+-+-+-+-+==========+-+-+-+-+-+" << endl;
    // unfollow(server, "paul.weng", "marstin");
    // refresh(server, "paul.weng");
    // cout << "+-+-+-+-+-+==========+-+-+-+-+-+" << endl;
    // for (int i = 0; i < server.users[0].num_following - 1; i++)
    // {
    //     cout << server.users[0].following[i]->username << " ";
    // }
    // cout << endl;
    // for (int i = 0; i < server.users[3].num_followers - 1; i++)
    // {
    //     cout << server.users[3].follower[i]->username << " ";
    // }
    // cout << endl;
    // //follow(server, "paul.weng", "marstin");
    // for (int i = 0; i < server.users[0].num_following - 1; i++)
    // {
    //     cout << server.users[0].following[i]->username << " ";
    // }
    // cout << endl;
    // for (int i = 0; i < server.users[3].num_followers - 1; i++)
    // {
    //     cout << server.users[3].follower[i]->username << " ";
    // }
    // cout << endl;

    // refresh(server, "marstin");
    // visit(server, "marstin", "paul.weng");
    // visit(server, "marstin", "fyq990508");
    // visit(server, "marstin", "yinguoxin2017");
    // visit(server, "marstin", "marstin");
    // visit(server, "paul.weng", "leepace666666");

    // for (unsigned int i = 0; i < server.num_tags; i++)
    // {
    //     cout << server.tags[i].tag_content << endl;
    // }
    // cout << server.num_tags << endl;

    //-------Read log--------
    string lpath = string(logpath);
    ifstream logfile(lpath);
    checkFileValidity(logfile, logpath);
    string line_buffer;
    string buffer;
    //bool receivePost = false;
    while (logfile.peek() != EOF)
    {
        getline(logfile, line_buffer);
        istringstream iStream;
        iStream.str(line_buffer);
        iStream >> buffer;
        if (buffer == "trending")
        {
            unsigned int trending_count;
            iStream >> trending_count;
            trending(server, trending_count);
        }
        else
        {
            string user1 = buffer;
            iStream >> buffer;
            if (buffer == "refresh")
            {
                refresh(server, user1);
            }
            else if (buffer == "visit")
            {
                iStream >> buffer;
                string user2 = buffer;
                visit(server, user1, user2);
            }
            else if (buffer == "follow")
            {
                iStream >> buffer;
                string user2 = buffer;
                follow(server, user1, user2);
            }
            else if (buffer == "unfollow")
            {
                iStream >> buffer;
                string user2 = buffer;
                follow(server, user1, user2); // TODO: UNFO
            }
            else if (buffer == "delete")
            {
                unsigned int post_id;
                iStream >> post_id;
                unpost(server, user1, post_id);
            }
        }
    }
    logfile.close();
}

void serverInit(Server_t &server, const char *fpath)
{
    string filepath = string(fpath);
    ifstream username_list(filepath);
    checkFileValidity(username_list, fpath);
    unsigned int username_n = 0;
    string buffer;
    while (getline(username_list, buffer))
    {
        username_n++;
    } // Count length before further operations
    try
    {
        ostringstream oStream;
        if (username_n > MAX_USERS)
        {
            oStream << "Error: Too many users!" << endl;
            oStream << "Maximal number of users is " << MAX_USERS << "." << endl;
            throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
        }
    }
    catch (const Exception_t &exception)
    {
        throw exception;
    }
    username_list.clear();
    username_list.seekg(0, ios::beg); // Rewind for reading
    unsigned int users_i = 0;
    username_n--; // The first line is redundant
    getline(username_list, buffer);
    server.fpath = buffer + "/";
    while (getline(username_list, buffer))
    {
        server.users[users_i].username = buffer;
        users_i++;
    }
    server.num_users = username_n;
    username_list.close();
}

void readUserInfo(Server_t &server)
{
    for (unsigned int user_i = 0; user_i < server.num_users; user_i++)
    {
        string userinfo_dir = server.fpath + server.users[user_i].username;
        string userinfo_file = userinfo_dir + "/user_info";
        string buffer;
        ifstream user_info(userinfo_file);
        try
        {
            checkFileValidity(user_info, userinfo_file.c_str());
        }
        catch (const Exception_t &exception)
        {
            throw exception;
        }
        // Get posts
        unsigned int num_posts;
        user_info >> num_posts;
        // cout << server.users[user_i].username << " posts: " << num_posts << endl; // XXX: CONS
        string capacityObject = "posts";
        try
        {
            checkCapacity(num_posts, capacityObject, server.users[user_i].username);
        }
        catch (const Exception_t &exception)
        {
            throw exception;
        }
        server.users[user_i].num_posts = num_posts;
        string post_dir;
        for (unsigned int post_i = 0; post_i < num_posts; post_i++)
        {
            server.users[user_i].posts[post_i].owner = &(server.users[user_i]);
            // Create the post, link it to the owner.
            ostringstream post_dir;
            post_dir << userinfo_dir << "/posts/" << (post_i + 1);
            ifstream post_info(post_dir.str());
            try
            {
                checkFileValidity(post_info, post_dir.str().c_str());
            }
            catch (const Exception_t &exception)
            {
                throw exception;
            }
            string buffer;
            getline(post_info, buffer);
            server.users[user_i].posts[post_i].title = buffer;
            // cout << buffer << endl; // XXX: CONS
            unsigned int tags_i = 0;
            while (post_info >> buffer)
            {
                if ((buffer.find("#") == 0) && (buffer.rfind("#") == buffer.length() - 1))
                {
                    string capacityObject = "tags";
                    try
                    {
                        checkCapacity(tags_i + 1, capacityObject, server.users[user_i].posts[post_i].title);
                    }
                    catch (const Exception_t &exception)
                    {
                        throw exception;
                    }
                    string tag_str = buffer.substr(1, buffer.length() - 2);
                    server.users[user_i].posts[post_i].tags[tags_i] = tag_str;
                    addTagtoServer(tag_str, server); // Also add to server's tag lib.
                    tags_i++;
                }
                else
                {
                    break;
                }
            }
            string buffer2;
            getline(post_info, buffer2);
            server.users[user_i].posts[post_i].num_tags = tags_i;
            server.users[user_i].posts[post_i].text = buffer + buffer2;
            // cout << server.users[user_i].username << " post " << buffer + buffer2 << " tag " << tags_i << endl; // XXX: CONS

            // Title, tags and text.

            unsigned int num_likes;
            post_info >> num_likes;
            // cout << "-likes: " << num_likes << endl; // XXX: CONS
            string capacityObject = "likes";
            try
            {
                checkCapacity(num_likes, capacityObject, server.users[user_i].posts[post_i].title);
            }
            catch (const Exception_t &exception)
            {
                throw exception;
            }

            server.users[user_i].posts[post_i].num_likes = num_likes;
            for (unsigned int likes_i = 0; likes_i < num_likes; likes_i++)
            {
                post_info >> buffer;
                int liker_i = findUser(buffer, server);
                if (liker_i != -1)
                {
                    server.users[user_i].posts[post_i].like_users[likes_i] = &(server.users[liker_i]);
                }
                // cout << buffer << endl; // XXX: CONS
            }
            // Likes
            unsigned int num_comments;
            post_info >> num_comments;
            // cout << "comments: " << num_comments << endl; // XXX: CONS
            capacityObject = "comments";
            try
            {
                checkCapacity(num_comments, capacityObject, server.users[user_i].posts[post_i].title);
            }
            catch (const Exception_t &exception)
            {
                throw exception;
            }
            server.users[user_i].posts[post_i].num_comments = num_comments;
            post_info.get();
            for (unsigned int comments_i = 0; comments_i < num_comments; comments_i++)
            {
                getline(post_info, buffer);
                int commentor_i = findUser(buffer, server);
                // cout << buffer << ": " << endl; // XXX: CONS
                getline(post_info, buffer);
                string comment_content = buffer;
                if (commentor_i != -1)
                {
                    server.users[user_i].posts[post_i].comments[comments_i].user = &(server.users[commentor_i]);
                    server.users[user_i].posts[post_i].comments[comments_i].text = comment_content;
                }
                // cout << buffer << endl; // XXX: CONS
            }
            post_info.close();
        }
        // Get following
        unsigned int num_following;
        user_info >> num_following;
        // cout << "-following: " << num_following << endl; // XXX: CONS
        capacityObject = "followings";
        try
        {
            checkCapacity(num_following, capacityObject, server.users[user_i].username);
        }
        catch (const Exception_t &exception)
        {
            throw exception;
        }

        server.users[user_i].num_following = num_following;
        user_info.get();
        for (unsigned int following_i = 0; following_i < num_following; following_i++)
        {
            getline(user_info, buffer);
            int following_user_i = findUser(buffer, server);
            if (following_user_i != -1)
            {
                server.users[user_i].following[following_i] = &(server.users[following_user_i]);
            }
            // cout << buffer << endl; // XXX: CONS
        }

        // Get followers
        unsigned int num_followers;
        user_info >> num_followers;
        capacityObject = "followers";
        // cout << "-follower: " << num_followers << endl; // XXX: CONS
        capacityObject = "followers";
        try
        {
            checkCapacity(num_followers, capacityObject, server.users[user_i].username);
        }
        catch (const Exception_t &exception)
        {
            throw exception;
        }
        server.users[user_i].num_followers = num_followers;
        user_info.get();
        for (unsigned int followers_i = 0; followers_i < num_followers; followers_i++)
        {
            getline(user_info, buffer);
            int follower_user_i = findUser(buffer, server);
            if (follower_user_i != -1)
            {
                server.users[user_i].follower[followers_i] = &(server.users[follower_user_i]);
            }
            // cout << buffer << endl;// XXX: CONS
        }
        user_info.close();
        // cout << "--------" << endl; // XXX: CONS
    }
}

void unpost(Server_t &server, string user1, unsigned int post_id)
{
    cout << ">> delete" << endl;
    int user_1_i = findUser(user1, server);
    if (server.users[user_1_i].num_posts < post_id)
    {
        cout << "ERROR" << endl; //TODO: ERROR HANDLING
    }
    else
    {
        for (unsigned int user1_post_i = post_id - 1; user1_post_i < server.users[user_1_i].num_posts - 1; ++user1_post_i)
        {
            server.users[user_1_i].posts[user1_post_i] = server.users[user_1_i].posts[user1_post_i + 1];
        }
        server.users[user_1_i].num_posts--;
        server.users[user_1_i].posts[server.users[user_1_i].num_posts] = server.dummy_post;
    }
}

void follow(Server_t &server, string user1, string user2) // User1 follow User2
{
    cout << ">> follow" << endl;
    //TODO: CAPACITY_OVERFLOW
    //TODO: INVALID FOLLOW
    int user_1_i = findUser(user1, server);
    int user_2_i = findUser(user2, server);
    server.users[user_1_i].num_following++;
    server.users[user_2_i].num_followers++;
    unsigned int following_i = server.users[user_1_i].num_following - 1; // The index.
    unsigned int followers_i = server.users[user_2_i].num_followers - 1;
    server.users[user_1_i].following[following_i] = &(server.users[user_2_i]);
    server.users[user_2_i].follower[followers_i] = &(server.users[user_1_i]);
}

void unfollow(Server_t &server, string user1, string user2) // User1 unfollow User2

{
    //TODO: CAPACITY_OVERFLOW
    cout << ">> unfollow" << endl;
    int user_1_i = findUser(user1, server);
    int user_2_i = findUser(user2, server);
    bool is_following = false;
    unsigned int user1_following_index = 0;
    unsigned int user2_follower_index = 0;
    for (unsigned int user2_follower_i = 0; user2_follower_i < server.users[user_2_i].num_followers; ++user2_follower_i)
    {
        if (server.users[user_2_i].follower[user2_follower_i]->username == user1)
        {
            is_following = true;
            user2_follower_index = user2_follower_i;
        }
    } // First traverse all followers of user2, confirming user1 is in it and also getting index.
    if (is_following)
    {
        for (unsigned int user2_follower_i = user2_follower_index; user2_follower_i < server.users[user_2_i].num_followers - 1; ++user2_follower_i)
        {
            server.users[user_2_i].follower[user2_follower_i] = server.users[user_2_i].follower[user2_follower_i + 1];
            for (int i = 0; i < server.users[user_2_i].num_followers - 1; i++)
            {
                cout << server.users[user_2_i].follower[i]->username << " ";
            }
            cout << endl;
        }
    }
    for (unsigned int user1_following_i = 0; user1_following_i < server.users[user_1_i].num_following; ++user1_following_i)
    {
        if (server.users[user_1_i].following[user1_following_i]->username == user2)
        {
            user1_following_index = user1_following_i;
        }
    }
    for (unsigned int user1_following_i = user1_following_index; user1_following_i < server.users[user_1_i].num_following - 1; ++user1_following_i)
    {

        server.users[user_1_i].following[user1_following_i] = server.users[user_1_i].following[user1_following_i + 1];
    }
    server.users[user_1_i].num_following--;
    server.users[user_2_i].num_followers--;
    server.users[user_1_i].following[server.users[user_1_i].num_following] = &(server.dummy_user);
    server.users[user_2_i].follower[server.users[user_2_i].num_followers] = &(server.dummy_user);
}

void refresh(Server_t &server, string user)
{
    cout << ">> refresh" << endl;
    int user_i = findUser(user, server);
    if (user_i != -1)
    {
        for (unsigned int post_i = 0; post_i < server.users[user_i].num_posts; post_i++)
        {
            printPost(server.users[user_i].posts[post_i]);
        }
        for (unsigned int following_i = 0; following_i < server.users[user_i].num_following; following_i++)
        {
            for (unsigned int post_i = 0; post_i < server.users[user_i].following[following_i]->num_posts; post_i++)
            {
                printPost(server.users[user_i].following[following_i]->posts[post_i]);
            }
        }
    }
    else
    {
        //TODO: Handle USER_NOT_EXIST;
    }
}

void visit(Server_t &server, string user1, string user2) // User1 visit User2
{
    cout << ">> visit" << endl;
    cout << user2 << endl;
    int user_1_i = findUser(user1, server);
    int user_2_i = findUser(user2, server);
    // TODO: Handle USER_NOT_EXIST;
    string relationship_status = "";
    if (user1 != user2)
    {
        bool isFollowingUser2 = false;
        bool isFollowedByUser2 = false;
        for (unsigned int following_i = 0; following_i < server.users[user_2_i].num_following; following_i++)
        {
            if (server.users[user_2_i].following[following_i]->username == user1)
            {
                isFollowedByUser2 = true;
            }
        }
        for (unsigned int followed_i = 0; followed_i < server.users[user_1_i].num_following; followed_i++)
        {
            if (server.users[user_1_i].following[followed_i]->username == user2)
            {
                isFollowingUser2 = true;
            }
        }
        if (isFollowedByUser2 && isFollowingUser2)
        {
            relationship_status = "friend\n";
        }
        else if ((!isFollowedByUser2) && isFollowingUser2)
        {
            relationship_status = "following\n";
        }
        else if (isFollowedByUser2 && (!isFollowingUser2))
        {
            relationship_status = "followed\n";
        }
        else if ((!isFollowedByUser2) && (!isFollowingUser2))
        {
            relationship_status = "stranger\n";
        }
    }
    cout << relationship_status;
    cout << "Followers: " << server.users[user_2_i].num_followers << endl;
    cout << "Following: " << server.users[user_2_i].num_following << endl;
}

void trending(Server_t &server, unsigned int trending_count)
{
    cout << ">> trending" << endl;
    updateTagScore(server);
    sortTagsbyScore(server);
    // cout << server.num_tags << endl; // XXX: CONS
    if (server.num_tags > trending_count)
    {
        for (unsigned int tag_i = server.num_tags - 1; tag_i > server.num_tags - trending_count - 1; tag_i--)
        {
            printTag(server.tags[tag_i], (server.num_tags - tag_i));
        }
    }
    else
    {
        if (server.num_tags > 2)
        {
            for (unsigned int tag_i = server.num_tags - 1; tag_i > 1; tag_i--)
            {
                printTag(server.tags[tag_i], (server.num_tags - tag_i));
            }
            printTag(server.tags[1], (server.num_tags));
            printTag(server.tags[0], (server.num_tags));
        }
        else if (server.num_tags == 2)
        {
            printTag(server.tags[1], (server.num_tags));
            printTag(server.tags[0], (server.num_tags));
        }
        else if (server.num_tags == 1)
        {
            printTag(server.tags[0], (server.num_tags));
        }
    }
}
/* Helper Functions */

// Data Handling
void updateTagScore(Server_t &server)
{
    for (unsigned int tag_index = 0; tag_index < server.num_tags; tag_index++)
    {
        server.tags[tag_index].tag_score = 0;
    }
    for (unsigned int user_i = 0; user_i < server.num_users; user_i++)
    {
        for (unsigned int post_i = 0; post_i < server.users[user_i].num_posts; post_i++)
        {
            for (unsigned int tag_i = 0; tag_i < server.users[user_i].posts[post_i].num_tags; tag_i++)
            {
                int tag_index = findTag(server.users[user_i].posts[post_i].tags[tag_i], server);
                if (tag_index != -1)
                {
                    server.tags[tag_index].tag_score += (POST_SCORE + COMT_SCORE * server.users[user_i].posts[post_i].num_comments + LIKE_SCORE * server.users[user_i].posts[post_i].num_likes); // See server_type.h for const defs.
                }
            }
        }
    }
}

void addTagtoServer(const string tagname, Server_t &server)
{
    int tag_index = findTag(tagname, server);
    if (tag_index == -1)
    {
        server.tags[server.num_tags].tag_content = tagname;
        server.tags[server.num_tags].tag_score = 0; // Lazy load, save some memory.
        server.num_tags++;
    }
}

void sortTagsbyScore(Server_t &server) //XXX: Better sort algoritm? Bubble costs too much.
{
    if (server.num_tags > 1)
    {
        unsigned int score_buffer;
        string content_buffer;
        for (unsigned int tag_i = 0; tag_i < server.num_tags - 1; tag_i++)
        {
            for (unsigned int tag_j = 0; tag_j < server.num_tags - 1 - tag_i; tag_j++)
            {
                if ((server.tags[tag_j].tag_score > server.tags[tag_j + 1].tag_score) || ((server.tags[tag_j].tag_score == server.tags[tag_j + 1].tag_score) && (server.tags[tag_j].tag_content < server.tags[tag_j + 1].tag_content)))
                {
                    score_buffer = server.tags[tag_j].tag_score;
                    content_buffer = server.tags[tag_j].tag_content;
                    server.tags[tag_j].tag_score = server.tags[tag_j + 1].tag_score;
                    server.tags[tag_j].tag_content = server.tags[tag_j + 1].tag_content;
                    server.tags[tag_j + 1].tag_score = score_buffer;
                    server.tags[tag_j + 1].tag_content = content_buffer;
                }
            }
        }
    }
}

int findUser(const string username, const Server_t &server)
{
    for (unsigned int i = 0; i < server.num_users; i++)
    {
        if (server.users[i].username == username)
        {
            return i;
        }
    }
    return -1;
}

int findTag(const string tagname, const Server_t &server)
{
    for (unsigned int i = 0; i < server.num_tags; i++)
    {
        if (server.tags[i].tag_content == tagname)
        {
            return i;
        }
    }
    return -1;
}
// Error Handling

void checkFileValidity(ifstream &file, const char *fpath)
{
    try
    {
        if (!file.is_open())
        {
            ostringstream oStream;
            string filepath = string(fpath);
            oStream << "Error: Cannot open file " << filepath << "!" << endl;
            throw Exception_t(FILE_MISSING, oStream.str());
        }
    }
    catch (const Exception_t &exception)
    {
        throw exception;
    }
}

void checkCapacity(unsigned int in_capacity, string capacityObject, string errorObject_name)
{
    unsigned int CAPACITY;
    string errorObject = "user";
    if (capacityObject == "posts")
    {
        CAPACITY = MAX_POSTS;
    }
    else if (capacityObject == "followings")
    {
        CAPACITY = MAX_FOLLOWING;
    }
    else if (capacityObject == "followers")
    {
        CAPACITY = MAX_FOLLOWERS;
    }
    else if (capacityObject == "tags")
    {
        CAPACITY = MAX_TAGS;
        errorObject = "post";
    }
    else if (capacityObject == "likes")
    {
        CAPACITY = MAX_LIKES;
        errorObject = "post";
    }
    else if (capacityObject == "comments")
    {
        CAPACITY = MAX_COMMENTS;
        errorObject = "post";
    }
    else
    {
        CAPACITY = 0;
        errorObject = "ERROR";
    }

    try
    {
        if (in_capacity > CAPACITY)
        {
            ostringstream oStream;
            oStream << "Error: Too many " << capacityObject << " for " << errorObject << " " << errorObject_name << "!" << endl;
            oStream << "Maximal number of " << capacityObject << " is " << CAPACITY << "." << endl;
            throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
        }
    }
    catch (const Exception_t &exception)
    {
        throw exception;
    }
}

void printUser(User_t &user, const string &relationship)
{
    cout << user.username << endl;
    cout << relationship << endl;
    cout << "Followers: " << user.num_followers
         << "\nFollowing: " << user.num_following << endl;
}

void printPost(Post_t &post)
{
    cout << post.owner->username << endl;
    cout << post.title << endl;
    cout << post.text << endl;
    cout << "Tags: ";
    for (unsigned int i = 0; i < post.num_tags; ++i)
    {
        cout << post.tags[i] << " ";
    }
    cout << "\nLikes: " << post.num_likes << endl;
    if (post.num_comments > 0)
    {
        cout << "Comments:" << endl;
        for (unsigned int i = 0; i < post.num_comments; ++i)
        {
            cout << post.comments[i].user->username << ": "
                 << post.comments[i].text << endl;
        }
    }
    cout << "- - - - - - - - - - - - - - -" << endl;
}

void printTag(const Tag_t &tag, unsigned int rank)
{
    cout << rank << " " << tag.tag_content << ": " << tag.tag_score << endl;
};

void console(Server_t &server)
{
    for (unsigned int i = 0; i < server.num_users; i++) // XXX: CONSOLE
    {
        cout << server.users[i].username << " following " << server.users[i].num_following << ": " << endl;
        if (server.users[i].num_following > 0)
        {
            for (unsigned int j = 0; j < server.users[i].num_following; j++)
            {
                cout << server.users[i].following[j]->username << endl;
            }
            cout << "------------" << endl;
        }
    }
    cout << "-+-+-+-+-+-+-+-+-" << endl;
    for (unsigned int i = 0; i < server.num_users; i++) // XXX: CONSOLE
    {
        cout << server.users[i].username << " follower " << server.users[i].num_followers << ": " << endl;
        if (server.users[i].num_followers > 0)
        {
            for (unsigned int j = 0; j < server.users[i].num_followers; j++)
            {
                cout << server.users[i].follower[j]->username << endl;
            }
            cout << "------------" << endl;
        }
    }
    cout << "-+-+-+-+-+-+-+-+-" << endl;
    for (unsigned int i = 0; i < server.num_users; i++) // XXX: CONSOLE
    {
        if (server.users[i].num_posts > 0)
        {
            cout << server.users[i].username << " posts:" << endl;
            cout << server.users[i].num_posts << endl;
            for (unsigned int j = 0; j < server.users[i].num_posts; j++)
            {
                cout << "Tags: ";
                for (unsigned int k = 0; k < server.users[i].posts[j].num_tags; k++)
                {
                    cout << server.users[i].posts[j].tags[k] << " ";
                }
                cout << endl;
                cout << server.users[i].posts[j].title << ": " << server.users[i].posts[j].text << endl;
                if (server.users[i].posts[j].num_likes > 0)
                {
                    cout << "Likes: ";
                    for (unsigned int k = 0; k < server.users[i].posts[j].num_likes; k++)
                    {
                        cout << server.users[i].posts[j].like_users[k]->username << " ";
                    }
                    cout << endl;
                }
                if (server.users[i].posts[j].num_comments > 0)
                {
                    cout << "Comments: ";
                    for (unsigned int k = 0; k < server.users[i].posts[j].num_comments; k++)
                    {
                        cout << server.users[i].posts[j].comments[k].user->username << ": " << server.users[i].posts[j].comments[k].text << endl;
                    }
                    cout << endl;
                }
                cout << "------------" << endl;
            }
        }
    }
}