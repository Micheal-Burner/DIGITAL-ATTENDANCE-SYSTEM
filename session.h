#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <vector>
using namespace std;

class AttendanceSession {
public:
    string courseCode;
    string date;
    string startTime;
    int duration;
    vector<char> attendance; // P, A, L

    AttendanceSession() {}

    AttendanceSession(string c, string d, string t, int dur, int studentCount) {
        courseCode = c;
        date = d;
        startTime = t;
        duration = dur;
        attendance.resize(studentCount, 'A');
    }
};

#endif
