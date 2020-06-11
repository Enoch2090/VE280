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
    serverInit(server, userpath);
    readUserInfo(server);

    // refresh(server, "marstin");
    // visit(server, "marstin", "paul.weng");
    // visit(server, "marstin", "fyq990508");
    // visit(server, "marstin", "yinguoxin2017");
    // visit(server, "marstin", "marstin");
    // visit(server, "paul.weng", "leepace666666");
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
    while (getline(logfile, line_buffer))
    {

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
        cout << exception.error_info;
    }
    username_list.clear();
    username_list.seekg(0, ios::beg); // Rewind for reading
    unsigned int users_i = 0;
    username_n--; // The first line is redundant
    getline(username_list, buffer);
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
        string fpath = "users/";
        fpath += server.users[user_i].username;
        string userinfo_dir = fpath + "/user_info";
        ifstream user_info(userinfo_dir);
        istringstream iSstream;
        string buffer;
        // Get posts
        getline(user_info, buffer);
        iSstream.str(buffer);
        unsigned int num_posts;
        iSstream >> num_posts;
        string capacityObject = "posts";
        checkCapacity(num_posts, capacityObject, server.users[user_i].username);
        server.users[user_i].num_posts = num_posts;
        string post_dir;
        for (unsigned int post_i = 0; post_i < num_posts; post_i++)
        {
            server.users[user_i].posts[post_i].owner = &(server.users[user_i]);
            // Create the post, link it to the owner.
            ostringstream post_dir;
            post_dir << fpath << "/posts/" << (post_i + 1);
            ifstream post_info(post_dir.str());
            string buffer;
            getline(post_info, buffer);
            server.users[user_i].posts[post_i].title = buffer;
            unsigned int tags_i = 0;
            while (getline(post_info, buffer))
            {
                if ((buffer.find("#") == 0) && (buffer.rfind("#") == buffer.length() - 1))
                {
                    string capacityObject = "tags";
                    checkCapacity(tags_i + 1, capacityObject, server.users[user_i].posts[post_i].title);
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
            server.users[user_i].posts[post_i].num_tags = tags_i;
            server.users[user_i].posts[post_i].text = buffer;
            // Title, tags and text.

            getline(post_info, buffer);
            iSstream.str(buffer);
            cout << buffer << " ";
            unsigned int num_likes;
            iSstream >> num_likes;
            cout << num_likes << endl;
            string capacityObject = "likes";
            checkCapacity(num_likes, capacityObject, server.users[user_i].posts[post_i].title);
            server.users[user_i].posts[post_i].num_likes = num_likes;
            for (unsigned int likes_i = 0; likes_i < num_likes; likes_i++)
            {
                getline(post_info, buffer);
                int liker_i = findUser(buffer, server);
                if (liker_i != -1)
                {
                    server.users[user_i].posts[post_i].like_users[likes_i] = &(server.users[liker_i]);
                }
            }
            // Likes

            getline(post_info, buffer);
            iSstream.str(buffer);
            unsigned int num_comments;
            iSstream >> num_comments;
            capacityObject = "comments";
            checkCapacity(num_comments, capacityObject, server.users[user_i].posts[post_i].title);
            server.users[user_i].posts[post_i].num_comments = num_comments;
            for (unsigned int comments_i = 0; comments_i < num_comments; comments_i++)
            {
                getline(post_info, buffer);
                int commentor_i = findUser(buffer, server);
                getline(post_info, buffer);
                string comment_content = buffer;
                if (commentor_i != -1)
                {
                    server.users[user_i].posts[post_i].comments[comments_i].user = &(server.users[commentor_i]);
                    server.users[user_i].posts[post_i].comments[comments_i].text = comment_content;
                }
            }
            post_info.close();
        }
        // Get following
        getline(user_info, buffer);
        iSstream.str(buffer);
        unsigned int num_following;
        iSstream >> num_following;
        capacityObject = "followings";
        checkCapacity(num_following, capacityObject, server.users[user_i].username);
        server.users[user_i].num_following = num_following;
        for (unsigned int following_i = 0; following_i < num_following; following_i++)
        {
            getline(user_info, buffer);
            int following_user_i = findUser(buffer, server);
            if (following_user_i != -1)
            {
                server.users[user_i].following[following_i] = &(server.users[following_user_i]);
            }
        }
        // Get followers
        getline(user_info, buffer);
        iSstream.str(buffer);
        unsigned int num_followers;
        iSstream >> num_followers;
        capacityObject = "followers";
        checkCapacity(num_followers, capacityObject, server.users[user_i].username);
        server.users[user_i].num_followers = num_followers;
        for (unsigned int followers_i = 0; followers_i < num_followers; followers_i++)
        {
            getline(user_info, buffer);
            int follower_user_i = findUser(buffer, server);
            if (follower_user_i != -1)
            {
                server.users[user_i].follower[followers_i] = &(server.users[follower_user_i]);
            }
        }
        user_info.close();
    }
}

void follow(Server_t &server, string user1, string user2) // User1 follow User2
{
    cout << ">> follow" << endl;
    //TODO: CAPACITY_OVERFLOW
    int user_1_i = findUser(user1, server);
    int user_2_i = findUser(user2, server);
    server.users[user_1_i].num_following++;
    server.users[user_2_i].num_followers++;
    unsigned int following_i = server.users[user_1_i].num_following - 1; // The index.
    unsigned int followers_i = server.users[user_2_i].num_followers - 1;
    server.users[user_1_i].following[following_i] = &(server.users[user_2_i]);
    server.users[user_2_i].following[followers_i] = &(server.users[user_1_i]);
}

void unfollow(Server_t &server, string user1, string user2) // User1 unfollow User2

{
    //TODO: CAPACITY_OVERFLOW
    // ????WTF
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
        cout << exception.error_info;
        // TODO: Multiple try and catch blocks.
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
        cout << exception.error_info;
        exit(0);
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