/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */

#include "simulation.h"
using namespace std;
// TODO: Define your functions
/* Simulation Process Functions */

void simulation(const char *userpath, const char *logpath)
{ // Main simulation function
    //------Read users------
    User_list *users = getUsers(userpath);
    cout << users->size << endl;
    for (int i = 0; i < users->size; i++)
    {
        cout << **(users->username + i) << endl;
    }
    //-------Read log--------
    ifstream logfile = openFile(logpath);
    string buffer;
    while (getline(logfile, buffer))
    {
        // cout << buffer << endl;
    }
    logfile.close();
    delete users;
}

User_list *getUsers(const char *fpath)
{
    ifstream username_list = openFile(fpath);
    int username_n = 0;
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
            oStream << "Too many users! " << endl;
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
    string **usernames = new string *[MAX_USERS];
    int i = 0;
    while (getline(username_list, buffer))
    {
        string *username = new string;
        *username = buffer;
        usernames[i] = username;
        i++;
    }
    User_list *user_list = new User_list; // Init data for usernames
    user_list->size = username_n;
    user_list->username = &usernames[0];
    username_list.close();
    return user_list;
}

/* Helper Functions */

// File Handling

ifstream openFile(const char *fpath)
{
    string filepath = string(fpath);
    ifstream file(filepath);
    try
    {
        ostringstream oStream;
        if (!file.is_open())
        {
            oStream << "Cannot open file " << filepath << endl;
            throw Exception_t(FILE_MISSING, oStream.str());
        }
    }
    catch (const Exception_t &exception)
    {
        cout << exception.error_info;
        exit(0);
    }
    return file;
}

// Printing

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
}
