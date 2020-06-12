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

// TODO: Declare your functions in this header file.
// Hint: You may need these request handling functions.

/* Simulation Process Functions */
void simulation(const char *userpath, const char *logpath);
void serverInit(Server_t &server, const char *fpath);
void readUserInfo(Server_t &server);

/* Simulation Action Functions */
void unpost(Server_t &server, string user1, unsigned int post_id);
void follow(Server_t &server, string user1, string user2);
void unfollow(Server_t &server, string user1, string user2);
void refresh(Server_t &server, string user);
void visit(Server_t &server, string user1, string user2);
void trending(Server_t &server, unsigned int trending_count);
/*
void visit(...);
void trending(...);
void refresh(...);
void follow(...);
void unfollow(...);
void like(...);
void unlike(...);
void comment(...);
void uncomment(...);
void post(...);
void unpost(...);
*/

/* Helper Functions */
// Data Handling
void updateTagScore(Server_t &server);
void sortTagsbyScore(Server_t &server);
void addTagtoServer(const string tagname, Server_t &server);
int findUser(const string username, const Server_t &server);
int findTag(const string tagname, const Server_t &server);
// File Handling

// Error Handling

void checkFileValidity(ifstream &file, const char *fpath);
void checkCapacity(unsigned int in_capacity, string capacityObject, string errorObject_name);

// Printing
void printUser(User_t &user, const string &relationship);
void printPost(Post_t &post);
void printTag(const Tag_t &tag, unsigned int rank);

void console(Server_t &server);