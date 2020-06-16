/*
 * This is VE280 Project 2, SU2020.
 * Header and starter files written by Ziqiao Ma and Zhuoer Zhu.
 * The rest of the shitty code is written by Yucheng Gu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */

#ifndef SERVER_TYPE_H
#define SERVER_TYPE_H

#include <string>

using namespace std;

/* Constants */
// Max number of users in the server
const unsigned int MAX_USERS = 20;

// Max number of followers per user
const unsigned int MAX_FOLLOWERS = 20;

// Max number of following per user
const unsigned int MAX_FOLLOWING = 20;

// Max number of posts per user
const unsigned int MAX_POSTS = 50;

// Max number of likes per post
const unsigned int MAX_LIKES = 20;

// Max number of comments per post
const unsigned int MAX_COMMENTS = 50;

// Max number of tags per post
const unsigned int MAX_TAGS = 5;

const int POST_SCORE = 5;

const int COMT_SCORE = 3;

const int LIKE_SCORE = 1;
/* Exception */
enum Error_t
{
    INVALID_ARGUMENT,
    FILE_MISSING,
    CAPACITY_OVERFLOW,
    INVALID_LOG,
};

struct Exception_t : public exception
{
    Error_t error;
    string error_info;
    Exception_t(Error_t err, const string &info)
    {
        this->error = err;
        this->error_info = info;
    }
};

/* Compound Types Declaration */
struct Comment_t;
struct Tag_t;
struct Post_t;
struct User_t;

struct Comment_t
/*
// Type: Comment_t
// ------------------
// The type Comment_t is used to represent a comment
// It consists of:
// * text: text of comment
// * user: pointer to the user who posted that comment
*/
{
    string text;
    User_t *user;
};

struct Tag_t
/*
// Type: Tag_t
// ------------------
// The type Tag_t is used to represent a tag
// It consists of:
// * tag_content: the content of the tag
// * tag_score: the score of the tag used to determine the trend
*/
{
    string tag_content;
    unsigned int tag_score;
};

struct Post_t
/*
// Type: Post_t
// ------------------
// The type Comment_t is used to represent a post
// It consists of:
// * comments: An array of comments
// * like_users: An array of pointers to the users who like this post
// * tags: An array of tag contents of this post
// * owner: A pointer to the post owner
// * title: the title of the post
// * text: the text of the post
// * num_likes: the number of likes
// * num_comments: the number of comments
*/
{
    Comment_t comments[MAX_COMMENTS];
    User_t *like_users[MAX_LIKES];
    string tags[MAX_TAGS];
    User_t *owner;
    string title;
    string text;
    unsigned int num_likes;
    unsigned int num_comments;
    unsigned int num_tags;
};

struct User_t
/*
// Type: User_t
// ------------------
// The type Comment_t is used to represent a user
// It consists of:
// * posts: An array of posts
// * following: An array of following usernames
// * follower: An array of followers
// * name: the username of user
// * num_posts: the number of posts
// * num_following: the number of following users
// * num_follower: the number of followers
*/
{
    Post_t posts[MAX_POSTS];
    User_t *following[MAX_FOLLOWING];
    User_t *follower[MAX_FOLLOWERS];
    string username;
    unsigned int num_posts;
    unsigned int num_following;
    unsigned int num_followers;
};

struct Server_t
/*
// Type: Server_t
// ------------------
// The type Server_t is used to represent the server.
// It consists of:
// * users: An array of users
// * num_users: the number of users
// * num_tags: the number of tags
// * dummy_user: an empty user
// * dummy_post: an empty post
// * dummy_comment: an empty comment
// * 
// *
*/
{
    User_t users[MAX_USERS];
    Tag_t tags[MAX_TAGS * MAX_POSTS * MAX_USERS];
    User_t dummy_user;
    Post_t dummy_post;
    Comment_t dummy_comment;
    unsigned int num_users;
    unsigned int num_tags;
    string fpath;
};

#endif // SERVER_TYPE_H
