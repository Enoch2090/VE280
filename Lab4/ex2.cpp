#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

struct Apple
{
    double price;
    double weight;
    string name;
};

int main(int argc, char *argv[])
{
    string filename;
    if (argc == 2)
    {
        filename = argv[1];
    }
    else
    {
        filename = "price_list.txt";
    }
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: file doe not exist." << endl;
    }
    else
    {
        Apple cheapest;
        double min_price = 1.79769e+308;
        string buffer;
        while (getline(file, buffer))
        {
            istringstream iStream;
            double price;
            double weight;
            double avr_price;
            string name;
            iStream.str(buffer);
            iStream >> name >> price >> weight;
            avr_price = price / weight;
            if (avr_price < min_price)
            {
                cheapest.price = price;
                cheapest.weight = weight;
                cheapest.name = name;
                min_price = avr_price;
            }
        }
        cout.setf(ios::fixed, ios::floatfield);
        cout
            << cheapest.name << " " << setprecision(2) << cheapest.price << " " << cheapest.weight << endl;
    }
    return 0;
}