#include <iostream>

using namespace std;

template <typename T>
struct ListNode {
    ListNode(T const &x, ListNode *_next=nullptr) : data(x), next(_next) {}
    ~ListNode() { delete next; }
    T data;
    ListNode *next;
};

template <typename T>
struct ListIterator {
    explicit ListIterator(ListNode<T> *_current=nullptr) 
    {
        this->current = _current;
    }
    ListNode<T> *current;

    ListIterator<T> &operator++() 
    { 
        this->current = this->current->next;
        return *this; 
    }

    T const &operator*() const 
    { 
        return this->current->data;
    }

    bool operator!=(ListIterator<T> const &x) const 
    {
        return !(this->current == x.current);
    }
};

template <typename T>
struct LinkedList {
    LinkedList() : front(nullptr), back(nullptr) {}
    ~LinkedList() { delete front; }
    ListNode<T> *front, *back;
    void add_back(T const &x) 
    {
        if (this->front == nullptr && this->back == nullptr)
        {
            ListNode<T> *temp = new ListNode<T>(x);
            this->front = temp;
            this->back = temp;
        }
        else
        {
            ListNode<T> *temp = new ListNode<T>(x);
            this->back->next = temp;
            this->back = temp;
        }
    }
    void add_front(T const &x) {
        if (this->front == nullptr && this->back == nullptr)
        {
            ListNode<T> *temp = new ListNode<T>(x);
            this->front = temp;
            this->back = temp;
        }
        else
        {
            ListNode<T> *temp = new ListNode<T>(x);
            temp->next = this->front;
            this->front = temp;
        }
    }
    ListIterator<T> begin() { return ListIterator<T>(this->front);}
    ListIterator<T> end() { return ListIterator<T>(nullptr);}
};

int main() {
    LinkedList<int> ll;

    // add a bunch of stuff
    for (int i = 0; i < 5; ++i) {
        ll.add_front(i * 3);
        ll.add_back(i * 7 + 1);
    }

    // print everything using the iterator interface
    for (ListIterator<int> i = ll.begin(); i != ll.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;

    // expected output: "12 9 6 3 0 1 8 15 22 29 "

    return 0;
}

