#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <utility>

using namespace std;

int main() 
{
    ofstream out;
    int lines = 0;

    mt19937 generator{random_device{}()};
    //modify range according to your need "A-Z","a-z" or "0-9" or whatever you need.
    uniform_int_distribution<int> distribution{'a', 'z'};
    string isServer = "_server";
    srand(time(0));

    int length = 0;
    vector<pair<string, string>> output;

    for (int i = 0; i < 3000; i++)
    {
        string rand_str(1, '\0');
        for(auto& dis: rand_str)
            dis = distribution(generator);
        int canBeServer = rand()%2;
        if (canBeServer == 0)
        {
            rand_str = rand_str + isServer;
        }
        string rand_str2(1, '\0');
        for(auto& dis: rand_str2)
            dis = distribution(generator);
        canBeServer = rand()%2;
        if (canBeServer == 0)
        {
            rand_str2 = rand_str2 + isServer;
        }

        if (rand_str2 != rand_str)
        {
            pair<string,string> temp = make_pair(rand_str, rand_str2);
            if (output.size() == 0)
            {
                output.push_back(temp);
            }
            else
            {
                bool unique = true;
                for (int j = 0; j < output.size(); j++)
                {
                    if (output[j] == temp)
                    {
                        unique = false;
                        j = output.size();
                    }
                }
                if (unique)
                {
                    output.push_back(temp);
                }
            }
        }
    }

    out.open("input.txt");

    out << output.size() << endl;

    for (int i = 0; i < output.size(); i++)
    {
        out << output[i].first << " " << output[i].second << " ";
        out << rand()%100 << endl;
    }


    return 0;
}