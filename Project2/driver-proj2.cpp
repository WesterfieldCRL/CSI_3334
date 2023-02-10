#include <iostream>

using namespace std;

int main()
{
    string word1 = "Test";
    cout << word1 << endl;
    string word2 = "vibe Chzeck";
    word1.insert(4, 1, 'a');
    cout << word1 << endl;
    return 0;
}