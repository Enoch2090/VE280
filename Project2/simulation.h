/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */

#include "server_type.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/* Simulation Process Functions -------------------------*/

// REQUIRES: userpath, logpath be two char arrays.
// EFFECTS: Starts a simulation process in stack.
void simulation(const char *userpath, const char *logpath);

// REQUIRES: server be a Server_t object, fpath be a char array.
// MODIFIES: server
// EFFECTS: Fill the User_t array in server with usernames.
void serverInit(Server_t &server, const char *fpath);

// REQUIRES: server be a Server_t object
// MODIFIES: server
// EFFECTS: Read each user's data, and parse them into the server structure.
void readUserInfo(Server_t &server);

/* Simulation Action Functions -------------------------*/
// Note: For all these functions, if the passed username is invalid, the call will be simply no effect. But they can handle such situation.

// REQUIRES: server be a Server_t object. user1, user2 two strings of usernames, post_id the ID of the post, comment_body a string of the comment.
// MODIFIES: server
// EFFECTS: Add comment by user1 to the specified post of user2.
void comment(Server_t &server, string user1, string user2, unsigned int post_id, string comment_body);

// REQUIRES: server be a Server_t object. user1, user2 two strings of usernames, post_id the ID of the post, comment_id the ID of the comment.
// MODIFIES: server
// EFFECTS: Delete comment specified by comment_id of user1 to the specified post of user2.
void uncomment(Server_t &server, string user1, string user2, unsigned int post_id, unsigned int comment_id);

// REQUIRES: server be a Server_t object. user1, user2 two strings of usernames, title the post title, tags[] an array of post tag strings, text a string of the post body, tag_num the length of tags[].
// MODIFIES: server
// EFFECTS: Add a post under user1.
void post(Server_t &server, string user1, string title, string tags[], string text, unsigned int tag_num);

// REQUIRES: server be a Server_t object. user1 a string of username, post_id the ID of the post.
// MODIFIES: server
// EFFECTS: Delete post specified by post_id of user1.
void unpost(Server_t &server, string user1, unsigned int post_id);

// REQUIRES: server be a Server_t object. user1, user2 two strings of usernames, post_id the ID of the post to like.
// MODIFIES: server
// EFFECTS: Add a like from user1 to the post specified by post_id of user2.
void like(Server_t &server, string user1, string user2, unsigned int post_id);

// REQUIRES: server be a Server_t object. user1, user2 two strings of usernames, post_id the ID of the post to like.
// MODIFIES: server
// EFFECTS: Undo the like from user1 to the post specified by post_id of user2.
void unlike(Server_t &server, string user1, string user2, unsigned int post_id);

// REQUIRES: server be a Server_t object. user1, user2 two strings of usernames.
// MODIFIES: server
// EFFECTS: Add user1 to user2's follower, and user2 to user1's following.
void follow(Server_t &server, string user1, string user2);

// REQUIRES: server be a Server_t object. user1, user2 two strings of usernames.
// MODIFIES: server
// EFFECTS: Delete user1 from user2's follower, and user2 from user1's following.
void unfollow(Server_t &server, string user1, string user2);

// REQUIRES: server be a Server_t object. user a string of username.
// EFFECTS: Print the posts that user refreshes.
void refresh(Server_t &server, string user);

// REQUIRES: server be a Server_t object. user1, user2 two strings of usernames.
// EFFECTS: Print the info of user2 that user1 visits.
void visit(Server_t &server, string user1, string user2);

// REQUIRES: server be a Server_t object. trending_count the number of tags to print.
// MODIFIES: server
// EFFECTS: First update tagscores stored in the server and sort tags by score. Then print out the most popular tags.
void trending(Server_t &server, unsigned int trending_count);

/* Helper Functions -------------------------*/
// Data Handling-----------

// REQUIRES: server be a Server_t object.
// MODIFIES: server
// EFFECTS: Update tagscores stored in the server.
void updateTagScore(Server_t &server);

// REQUIRES: server be a Server_t object.
// MODIFIES: server
// EFFECTS: Sort tags stored in the server by score.
void sortTagsbyScore(Server_t &server);

// REQUIRES: server be a Server_t object, tagname a string of tag.
// MODIFIES: server
// EFFECTS: Check whether tag specified by tagname is already in the server. If not, add it to the server.
void addTagtoServer(const string tagname, Server_t &server);

// REQUIRES: server be a Server_t object, username a string of username.
// EFFECTS: Check whether the user specified by username is in the server. If yes, return this user's index in the User_t array. If not, return -1.
int findUser(const string username, const Server_t &server);

// REQUIRES: server be a Server_t object, tagname a string of tag.
// EFFECTS: Check whether the tag specified by tagname is in the server. If yes, return this tag's index in the Tag_t array. If not, return -1.
int findTag(const string tagname, const Server_t &server);

// Error Handling-----------

// REQUIRES: file be a ifstream file object, fpath a char array of its file path.
// EFFECTS: Check whether the file is already opended. If not, raise an error.
void checkFileValidity(ifstream &file, const char *fpath);

// REQUIRES: in_capacity be an integer of the quantity to be checked, capacityObject a string of the object to be checked, errorObject_name a string of the name of the class of error object.
// EFFECTS: Check whether in_capacity meets the capacity of capacityObject. If not, raise an error according to errorObject_name.
void checkCapacity(unsigned int in_capacity, string capacityObject, string errorObject_name);

// Printing-----------

// REQUIRES: user a User_t object, relationship a string of the relationship.
// EFFECTS: Print the info of this user in standarized way.
void printUser(User_t &user, const string &relationship);

// REQUIRES: post a Post_t object.
// EFFECTS: Print the info of this post in standarized way.
void printPost(Post_t &post);

// REQUIRES: tag a Tag_t object, rank the rank of this tag in the server.
// EFFECTS: Print the info of this tag in standarized way.
void printTag(const Tag_t &tag, unsigned int rank);

// REQUIRES : server be a Server_t object.
// EFFECTS: Print out EVERYTHING in this server. Useful when debugging.
void console(Server_t &server);