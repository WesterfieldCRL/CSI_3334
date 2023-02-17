#include <iostream>
#include <fstream>
#include <string>
#include <random>

using namespace std;

int main() 
{
    ofstream out;
    int lines;
    string start;
    string end;

    mt19937 generator{random_device{}()};
    //modify range according to your need "A-Z","a-z" or "0-9" or whatever you need.
    uniform_int_distribution<int> distribution{'a', 'z'};

    srand(time(0));

    out.open("input-6.txt");

    lines = rand() % 20000;

    

    out << lines << "\n";

    for (int i = 0; i < lines; i++)
    {
        int generate_len = rand()%5 + 2;
        string rand_str(generate_len, '\0');
        for(auto& dis: rand_str)
            dis = distribution(generator);
        out << rand_str << "\n";
        if (i == 0)
        {
            start = rand_str;
        }
        else if (i == lines - 1)
        {
            end = rand_str;
        }
    }

    out << start << "\n";
    out << end << "\n";


    return 0;
}