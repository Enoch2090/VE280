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
    Server_t *server = serverInit(userpath);
    cout << server->num_users << " users." << endl; // XXX: CONSOLE
    readUserInfo(server);
    for (unsigned int i = 0; i < server->num_users; i++) // XXX: CONSOLE
    {
        cout << server->users[i]->username << " following " << server->users[i]->num_following << ": " << endl;
        if (server->users[i]->num_following > 0)
        {
            for (unsigned int j = 0; j < server->users[i]->num_following; j++)
            {
                cout << server->users[i]->following[j]->username << endl;
            }
            cout << "------------" << endl;
        }
    }
    cout << "-+-+-+-+-+-+-+-+-" << endl;
    for (unsigned int i = 0; i < server->num_users; i++) // XXX: CONSOLE
    {
        cout << server->users[i]->username << " follower " << server->users[i]->num_followers << ": " << endl;
        if (server->users[i]->num_followers > 0)
        {
            for (unsigned int j = 0; j < server->users[i]->num_followers; j++)
            {
                cout << server->users[i]->follower[j]->username << endl;
            }
            cout << "------------" << endl;
        }
    }
    //-------Read log--------
    string lpath = string(logpath);
    ifstream logfile(lpath);
    checkFileValidity(logfile, logpath);
    string buffer;
    while (getline(logfile, buffer))
    {
        // TODO: Read logfile
    }
    logfile.close();
    delete server;
}

Server_t *serverInit(const char *fpath)
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
            oStream << "Too many users!" << endl;
            oStream << "Maximal number of users is " << MAX_USERS << "." << endl;
            throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
        }
    }
    catch (const Exception_t &exception)
    {
        cout << exception.error_info;
        exit(0);
    }
    username_list.clear();
    username_list.seekg(0, ios::beg); // Rewind for reading
    unsigned int i = 0;
    username_n--;
    Server_t *server = new Server_t;
    getline(username_list, buffer);
    while (getline(username_list, buffer))
    {
        server->users[i] = new User_t;
        server->users[i]->username = buffer;

        i++;
    }
    server->num_users = username_n;
    username_list.close();
    return server;
}

void readUserInfo(Server_t *server)
{
    for (unsigned int user_i = 0; user_i < server->num_users; user_i++)
    {
        string fpath = "users/";
        fpath += server->users[user_i]->username;
        string userinfo = fpath + "/user_info";
        ifstream user_info(userinfo);
        string buffer;
        // Get posts
        getline(user_info, buffer);
        int num_posts = (unsigned int)stoi(buffer);
        checkCapacity(num_posts, "posts", server->users[user_i]->username);
        server->users[user_i]->num_posts = num_posts;
        for (unsigned int post_i = 1; post_i < num_posts + 1; post_i++)
        {
            //TODO: Read posts
        }
        // Get following
        getline(user_info, buffer);
        int num_following = (unsigned int)stoi(buffer);
        checkCapacity(num_following, "followings", server->users[user_i]->username);
        server->users[user_i]->num_following = num_following;
        for (unsigned int following_i = 0; following_i < num_following; following_i++)
        {
            getline(user_info, buffer);
            User_t *following = findUser(buffer, server);
            if (following->username != "USER NOT FOUND")
            {
                server->users[user_i]->following[following_i] = new User_t;
                server->users[user_i]->following[following_i] = following;
            }
        }
        // Get followers
        getline(user_info, buffer);
        int num_followers = (unsigned int)stoi(buffer);
        checkCapacity(num_followers, "followers", server->users[user_i]->username);
        server->users[user_i]->num_followers = num_followers;
        for (unsigned int followers_i = 0; followers_i < num_followers; followers_i++)
        {
            getline(user_info, buffer);
            User_t *follower = findUser(buffer, server);
            if (follower->username != "USER NOT FOUND")
            {
                server->users[user_i]->follower[followers_i] = new User_t;
                server->users[user_i]->follower[followers_i] = follower;
            }
        }
    }
}

/* Helper Functions */

// Data Handling

User_t *findUser(const string username, const Server_t *server)
{
    for (unsigned int i = 0; i < server->num_users; i++)
    {
        if (server->users[i]->username == username)
        {
            return server->users[i];
        }
    }
    User_t *NULL_USER = new User_t;
    NULL_USER->username = "USER NOT FOUND";
    return NULL_USER;
}

// File Handling

// Error Handling
void checkFileValidity(ifstream &file, const char *fpath)
{
    try
    {
        if (!file.is_open())
        {
            ostringstream oStream;
            string filepath = string(fpath);
            oStream << "Cannot open file " << filepath << endl;
            throw Exception_t(FILE_MISSING, oStream.str());
        }
    }
    catch (const Exception_t &exception)
    {
        cout << exception.error_info;
        exit(0);
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
            oStream << "Too many" << capacityObject << " for " << errorObject << " " << errorObject_name << " !" << endl;
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