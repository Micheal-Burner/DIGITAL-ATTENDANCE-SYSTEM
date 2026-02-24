#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "student.h"
#include "session.h"

using namespace std;

vector<Student> students;
vector<AttendanceSession> sessions;

/* ---------- STUDENT FILE HANDLING ---------- */
void loadStudents() {
    ifstream file("students.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, index;
        getline(ss, name, ',');
        getline(ss, index);
        students.emplace_back(name, index);
    }
    file.close();
}

void saveStudents() {
    ofstream file("students.txt");
    for (auto &s : students) {
        file << s.name << "," << s.indexNumber << endl;
    }
    file.close();
}

/* ---------- SESSION FILE HANDLING ---------- */
void saveSession(const AttendanceSession &s) {
    string filename = "session_" + s.courseCode + "_" + s.date + ".txt";
    ofstream file(filename);

    file << s.courseCode << endl;
    file << s.date << endl;
    file << s.startTime << endl;
    file << s.duration << endl;

    for (char a : s.attendance) {
        file << a << endl;
    }
    file.close();
}

/* ---------- STUDENT FUNCTIONS ---------- */
void registerStudent() {
    string name, index;
    cin.ignore();
    cout << "Enter student name: ";
    getline(cin, name);
    cout << "Enter index number: ";
    getline(cin, index);

    students.emplace_back(name, index);
    saveStudents();

    cout << "Student registered successfully!\n";
}

void viewStudents() {
    if (students.empty()) {
        cout << "No students registered.\n";
        return;
    }

    for (size_t i = 0; i < students.size(); i++) {
        cout << i + 1 << ". " << students[i].name
             << " (" << students[i].indexNumber << ")\n";
    }
}

/* ---------- SESSION FUNCTIONS ---------- */
void createSession() {
    string course, date, time;
    int duration;

    cin.ignore();
    cout << "Course code: ";
    getline(cin, course);
    cout << "Date (YYYY-MM-DD): ";
    getline(cin, date);
    cout << "Start time: ";
    getline(cin, time);
    cout << "Duration (hours): ";
    cin >> duration;

    AttendanceSession s(course, date, time, duration, students.size());
    sessions.push_back(s);

    cout << "Session created successfully!\n";
}

void markAttendance() {
    if (sessions.empty()) {
        cout << "No sessions available.\n";
        return;
    }

    int choice;
    cout << "Select session:\n";
    for (size_t i = 0; i < sessions.size(); i++) {
        cout << i + 1 << ". " << sessions[i].courseCode
             << " (" << sessions[i].date << ")\n";
    }
    cin >> choice;
    choice--;

    for (size_t i = 0; i < students.size(); i++) {
        char status;
        cout << students[i].name << " (P/A/L): ";
        cin >> status;
        status = toupper(status);

        if (status == 'P' || status == 'A' || status == 'L') {
            sessions[choice].attendance[i] = status;
        } else {
            sessions[choice].attendance[i] = 'A';
        }
    }

    saveSession(sessions[choice]);
    cout << "Attendance recorded successfully!\n";
}

void viewReport() {
    if (sessions.empty()) {
        cout << "No sessions available.\n";
        return;
    }

    int choice;
    cout << "Select session:\n";
    for (size_t i = 0; i < sessions.size(); i++) {
        cout << i + 1 << ". " << sessions[i].courseCode
             << " (" << sessions[i].date << ")\n";
    }
    cin >> choice;
    choice--;

    int p = 0, a = 0, l = 0;

    for (size_t i = 0; i < students.size(); i++) {
        char s = sessions[choice].attendance[i];
        cout << students[i].name << ": " << s << endl;

        if (s == 'P') p++;
        else if (s == 'L') l++;
        else a++;
    }

    cout << "\nSummary:\n";
    cout << "Present: " << p << endl;
    cout << "Late: " << l << endl;
    cout << "Absent: " << a << endl;
}

/* ---------- MAIN MENU ---------- */
int main() {
    loadStudents();

    int option;
    do {
        cout << "\n--- DIGITAL ATTENDANCE SYSTEM ---\n";
        cout << "1. Register Student\n";
        cout << "2. View Students\n";
        cout << "3. Create Attendance Session\n";
        cout << "4. Mark Attendance\n";
        cout << "5. View Attendance Report\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> option;

        switch (option) {
            case 1: registerStudent(); break;
            case 2: viewStudents(); break;
            case 3: createSession(); break;
            case 4: markAttendance(); break;
            case 5: viewReport(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (option != 0);

    return 0;
}
