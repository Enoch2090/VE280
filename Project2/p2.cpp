#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "server_type.h"
using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        if (argc < 3)
        {
            ostringstream oStream;
            oStream << "Error: Wrong number of arguments!" << endl;
            oStream << "Usage: ./p2 <username> <logfile>" << endl;
            throw Exception_t(INVALID_ARGUMENT, oStream.str());
        }
    }
    catch (const Exception_t &exception)
    {
        cout << exception.error_info;
        return 0;
    }
    string username_f = string(argv[1]);
    string logfile_f = string(argv[2]);
    cout << username_f << endl
         << logfile_f << endl;
    ifstream username_list(username_f);
    ifstream logfile_list(logfile_f);
    try
    {

        if (!username_list.is_open())
        {
            ostringstream oStream;
            oStream << "Cannot open file " << username_f << endl; // TODO: Simpler way of double error
            throw Exception_t(FILE_MISSING, oStream.str());
        }
        else if (!logfile_list.is_open())
        {
            ostringstream oStream;
            oStream << "Cannot open file " << logfile_f << endl;
            throw Exception_t(FILE_MISSING, oStream.str());
        }
    }
    catch (const Exception_t &exception)
    {
        cout << exception.error_info;
        return 0;
    }
    string buffer;
    while (getline(username_list, buffer))
    {
        cout << buffer << endl;
    }
    while (getline(logfile_list, buffer))
    {
        cout << buffer << endl;
    }
    username_list.close();
    logfile_list.close();
    return 0;
}