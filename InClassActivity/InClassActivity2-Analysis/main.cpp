#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

// A recursive function to simulate running an O(n^k) loop. It computes a
// meaningless value to force the compiler to run all the code (otherwise, a
// smart compiler can sometimes optimize out a function that can be
// pre-computed).
int run(int k, int n) {
    int result = 0;
    if (k == 0) {
        result = clock();
    } else {
        for (int i = 0; i < n; ++i) {
            result += run(k-1, n);
        }
    }
    return result;
}

// This program takes two command-line arguments: k and n (note the order).
int main(int argc, char **argv) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " k n\n";
        cerr << "where k is the polynomial degree, and n is the input size\n";
        return 1;
    }

    int k = stoi(argv[1]);
    int n = stoi(argv[2]);

    clock_t start = clock();
    int result = run(k, n);
    double seconds = ((double)(clock() - start) / CLOCKS_PER_SEC);
    cout << "n^" << k << " took " << fixed << setprecision(2) << seconds;
    cout << " seconds for n = " << n << endl;
    if (seconds < 0.05) {
        cout << "Times close to zero are not very meaningful; try a larger n.\n";
    }
    cout << "result = " << result << " (ignore this)\n";
    return 0;
}