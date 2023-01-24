#include <iostream>

using namespace std;

class Parent {
    protected:
        string name;
        string phoneNumber;
};

class Employee : Parent {
    private:
        int employeeNumber;
};
class Student : Parent {
    private:
        int studentID;
};