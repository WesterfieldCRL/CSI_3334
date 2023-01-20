#include <iostream>
int main(int argc, char **argv) {
    int n, sum = 0, x;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> x;
        sum += x;
        std::cout << x << " " << sum << " \n";
    }
    return 0;
}