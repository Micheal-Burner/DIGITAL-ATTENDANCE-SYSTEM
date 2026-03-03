#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <ctime>
#include <sstream>

using namespace std;

// --- Student Class ---
class Student {
private:
    string indexNumber;
    string name;

public:
    Student(string idx, string n) : indexNumber(idx), name(n) {}
    string getIndex() const { return indexNumber; }
    string getName() const { return name; }
    void saveToFile(ofstream& outFile) const {
        outFile << indexNumber << "," << name << "\n";
    }
};

struct AttendanceRecord {
    string studentIndex;
    string studentName; 
    string status;
};

class AttendanceSession {
private:
    string courseCode, date, startTime, duration;
    vector<AttendanceRecord> records;

public:
    AttendanceSession(string code, string dt, string st, string dur)
        : courseCode(code), date(dt), startTime(st), duration(dur) {}

    void addRecord(string index, string name, string status) {
        AttendanceRecord newRecord = {index, name, status};
        records.push_back(newRecord);
    }

    void saveToFile() const {
        string filename = "session_" + courseCode + "_" + date + ".csv";
        ofstream outFile(filename.c_str()); 
        if (outFile.is_open()) {
            outFile << "Course Code,Date,Start Time,Duration\n";
            outFile << courseCode << "," << date << "," << startTime << "," << duration << "\n\n";
            outFile << "Index Number,Student Name,Status\n";
            for (size_t i = 0; i < records.size(); ++i) {
                outFile << records[i].studentIndex << "," << records[i].studentName << "," << records[i].status << "\n";
            }
            outFile.close();
            cout << "\nSuccess! Excel file created: " << filename << endl;
        }
    }
};

void registerStudent(vector<Student>& students) {
    string index, name;
    cout << "Enter student index: "; cin >> index;
    cout << "Enter student name: "; 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    students.push_back(Student(index, name));
    ofstream outFile("students.csv", ios::app); 
    if (outFile.is_open()) {
        // If file is empty, write header first
        outFile.seekp(0, ios::end);
        if (outFile.tellp() == 0) outFile << "Index Number,Student Name\n";
        students.back().saveToFile(outFile);
        outFile.close();
    }
}

int main() {
    vector<Student> students;
    int choice = 0;
    while (choice != 3) {
        cout << "\n1. Register Student\n2. Mark Attendance (Excel)\n3. Exit\nChoice: ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        if (choice == 1) registerStudent(students);
        else if (choice == 2) {
            if (students.empty()) { cout << "No students registered!\n"; continue; }
            string code, start, dur;
            cout << "Course Code: "; cin >> code;
            cout << "Start Time: "; cin >> start;
            cout << "Duration: "; cin >> dur;
            AttendanceSession session(code, "2026_02_28", start, dur);
            for (size_t i = 0; i < students.size(); ++i) {
                string stat; cout << "Status for " << students[i].getName() << " (P/A): "; cin >> stat;
                session.addRecord(students[i].getIndex(), students[i].getName(), stat);
            }
            session.saveToFile();
        }
    }
    return 0;
}
