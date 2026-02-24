#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
using namespace std;

class Student {
public:
    string name;
    string indexNumber;

    Student() {}

    Student(string n, string i) {
        name = n;
        indexNumber = i;
    }
};

#endif
