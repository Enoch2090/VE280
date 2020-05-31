#include "server_type.h"
#include "simulation.h"
using namespace std;

int main(int argc, char *argv[])
{
    //----Check input args----
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
    simulation(argv[1], argv[2]);
    return 0;
}