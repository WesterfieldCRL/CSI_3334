#include <iostream>
#include <fstream>
#include <string>
#include <random>

using namespace std;

int main() 
{
    ofstream out;
    int lines = 0;

    mt19937 generator{random_device{}()};
    //modify range according to your need "A-Z","a-z" or "0-9" or whatever you need.
    uniform_int_distribution<int> distribution{'a', 'z'};

    srand(time(0));

    out.open("input.txt");

    out << "1000" << endl;
    for (int i = 0; i < 1000; i++)
    {
        out << lines << " ";
        out << rand()%10000 << " ";
        out << rand()%100 + 1 << " ";
        int generate_len = rand()%5 + 2;
        string rand_str(generate_len, '\0');
        for(auto& dis: rand_str)
            dis = distribution(generator);
        out << rand_str << "\n";

        lines += rand()%100;
    }


    return 0;
}