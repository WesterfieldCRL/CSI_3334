#include <iostream>
#include <vector>
#include <list>
#include <random>

using namespace std;

// Specialize a default HashFunc for int type.
struct DefaultIntHash { int operator()(int x) const { return x; } };

// Uncomment this and make your own hash function that behaves better for this
// program
struct YourIntHash { int operator()(int x) const { if (x%2 == 0){return x-1;}return x; } };

// hash table with a default hash function type
template <typename T, typename Hash>
class HashTable {
    public:
        HashTable(int size) : table(size), numItems(0) {}

        void insert(T const &item) {
            bool unique = true;
            for (auto const &entry : table[hash(item)%table.size()]) {
                if (entry == item) { unique = false; break; }
            }
            if (!unique) { return; }
            table[hash(item)%table.size()].push_back(item);
            numItems++;
        }

        void remove(T const &item) {
            int slot = hash(item)%table.size();
            for (auto i = table[slot].begin(); i != table[slot].end(); i++) {
                if (*i == item) {
                    table[slot].erase(i);
                    numItems--;
                    return;
                }
            }
            /*table[hash(item)%table.size()].remove(item);
            --numItems;*/ //I think this works as well?
        }

        void dump(ostream &os) const {
            for (int i = 0; i < table.size(); ++i) {
                os << i << ":";
                for (auto const &entry : table[i]) { os << " " << entry; }
                os << endl;
            }
        }

        double loadFactor() const { return (numItems) / static_cast<double>(table.size()); }

    private:
        vector<list<T>> table;
        int numItems;
        Hash hash;
};

int main(int argc, char **argv) {
    HashTable<int, YourIntHash> ht(7);

    // create a sequence to insert (and then remove)
    vector<int> sequence;
    for (int i = 1; i <= 5; ++i) {
        sequence.push_back(i * 3);
        sequence.push_back(i * 7 + 1);
    }

    // insert everything
    for (auto x : sequence) { ht.insert(x); }

    ht.dump(cout);
    cout << "Load factor: " << ht.loadFactor() << endl;

    // remove half of the things we inserted
    for (int i = 0; i < sequence.size() / 2; ++i) { ht.remove(sequence[i]); }

    ht.dump(cout);
    cout << "Load factor: " << ht.loadFactor() << endl;

    return 0;
}

/* Expected output with the default hash function:
-----
0:
1: 8 15 22 29 36
2: 9
3: 3
4:
5: 12
6: 6
Load factor: 1.28571
0:
1: 22 29 36
2:
3:
4:
5: 12
6:
Load factor: 0.571429
-----
 */