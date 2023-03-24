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

    out.open("input.txt");

    for (int i = 0; i < 100; i++)
    {
        int generate_len = rand()%5+1;
        string rand_str(generate_len, '\0');
        for(auto& dis: rand_str)
            dis = distribution(generator);
        int output = rand()%6;
        switch (output)
        {
        case 0:

            out << "i " << rand_str << endl;
            break;

        case 1:
            out << "p" << endl;
            break;
        
        case 2:
            out << "r " << rand_str << endl;
            break;

        case 3:
            out << "l" << endl;
            break;

        case 4:
            out << "e '";
            lines = rand()%10;
            for (int i = 0; i < lines; i++)
            {
                int generate_len = rand()%5+1;
                string rand_str(generate_len, '\0');
                for(auto& dis: rand_str)
                    dis = distribution(generator);
                out << rand_str << " ";
            }
            out << rand_str << "'" << endl;

            break;
        
        case 5:
            out << "d '";
            lines = rand()%10;
            for (int i = 0; i < lines; i++)
            {
                out << "r";
                for (int i = rand()%10; i > 0; i--)
                {
                    int randNum = rand()%2;
                    out << randNum;
                }
                out << " ";
            }
            out << "r";
            for (int i = rand()%10; i > 0; i--)
            {
                int randNum = rand()%2;
                out << randNum;
            }
            out << "'" << endl;

            break;
        default:
            break;
        }
    }
    out << "q" << endl;


    return 0;
}