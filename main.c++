#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

class Student {
public:
    string studentID;
    int rollNo;
    string name;
    string gender;
    string course;
    int year;
    float cgpa;

    void input() {
        cout << "Enter Student ID: ";
        cin >> studentID;
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        while (name.empty()) {
            cout << "Name cannot be empty. Re-enter: ";
            getline(cin, name);
        }
        cout << "Enter Gender (M/F/O): ";
        getline(cin, gender);
        while (gender.empty()) {
            cout << "Gender cannot be empty. Re-enter: ";
            getline(cin, gender);
        }
        cout << "Enter Course: ";
        getline(cin, course);
        while (course.empty()) {
            cout << "Course cannot be empty. Re-enter: ";
            getline(cin, course);
        }
        cout << "Enter Year (1-4): ";
        cin >> year;
        while (year < 1 || year > 4) {
            cout << "Year must be between 1 and 4. Re-enter: ";
            cin >> year;
        }
        cout << "Enter CGPA (0.0 - 10.0): ";
        cin >> cgpa;
        while (cgpa < 0.0 || cgpa > 10.0) {
            cout << "CGPA must be between 0.0 and 10.0. Re-enter: ";
            cin >> cgpa;
        }
    }

    void display() const {
        cout << "Student ID: " << studentID
             << ", Roll No: " << rollNo
             << ", Name: " << name
             << ", Gender: " << gender
             << ", Course: " << course
             << ", Year: " << year
             << ", CGPA: " << cgpa << endl;
    }

    string toCSV() const {
        return studentID + "," + to_string(rollNo) + "," + name + "," + gender + "," +
               course + "," + to_string(year) + "," + to_string(cgpa);
    }

    static Student fromCSV(const string &line) {
        Student s;
        stringstream ss(line);
        string rollStr, yearStr, cgpaStr;

        getline(ss, s.studentID, ',');
        getline(ss, rollStr, ',');
        getline(ss, s.name, ',');
        getline(ss, s.gender, ',');
        getline(ss, s.course, ',');
        getline(ss, yearStr, ',');
        getline(ss, cgpaStr, ',');

        s.rollNo = stoi(rollStr);
        s.year = stoi(yearStr);
        s.cgpa = stof(cgpaStr);

        return s;
    }
};

void addStudent() {
    Student s;
    s.input();
    ofstream out("students.dat", ios::app);
    out << s.toCSV() << endl;
    out.close();
    cout << "Record added successfully.\n";
}

void displayAll() {
    ifstream in("students.dat");
    if (!in) {
        cout << "No records found.\n";
        return;
    }

    string line;
    while (getline(in, line)) {
        Student s = Student::fromCSV(line);
        s.display();
    }

    in.close();
}

void searchStudent() {
    int roll;
    bool found = false;
    cout << "Enter Roll No to search: ";
    cin >> roll;

    ifstream in("students.dat");
    string line;
    while (getline(in, line)) {
        Student s = Student::fromCSV(line);
        if (s.rollNo == roll) {
            cout << "Record Found:\n";
            s.display();
            found = true;
            break;
        }
    }

    in.close();
    if (!found)
        cout << "Student with Roll No " << roll << " not found.\n";
}

void updateStudent() {
    int roll;
    bool found = false;
    cout << "Enter Roll No to update: ";
    cin >> roll;

    vector<Student> students;
    string line;
    ifstream in("students.dat");
    while (getline(in, line)) {
        Student s = Student::fromCSV(line);
        students.push_back(s);
    }
    in.close();

    for (auto &s : students) {
        if (s.rollNo == roll) {
            cout << "Old Record:\n";
            s.display();
            cout << "Enter New Details:\n";
            s.input();
            s.rollNo = roll; // preserve the original roll no
            found = true;
            break;
        }
    }

    if (found) {
        ofstream out("students.dat");
        for (const auto &s : students)
            out << s.toCSV() << endl;
        out.close();
        cout << "Record updated successfully.\n";
    } else {
        cout << "Student not found.\n";
    }
}

void deleteStudent() {
    int roll;
    bool found = false;
    cout << "Enter Roll No to delete: ";
    cin >> roll;

    vector<Student> students;
    string line;
    ifstream in("students.dat");
    while (getline(in, line)) {
        Student s = Student::fromCSV(line);
        if (s.rollNo != roll)
            students.push_back(s);
        else
            found = true;
    }
    in.close();

    ofstream out("students.dat");
    for (const auto &s : students)
        out << s.toCSV() << endl;
    out.close();

    if (found)
        cout << "Record deleted successfully.\n";
    else
        cout << "Record not found.\n";
}

void exportToText() {
    ifstream in("students.dat");
    ofstream out("students.txt");

    string line;
    while (getline(in, line)) {
        Student s = Student::fromCSV(line);
        out << "Student ID: " << s.studentID
            << ", Roll No: " << s.rollNo
            << ", Name: " << s.name
            << ", Gender: " << s.gender
            << ", Course: " << s.course
            << ", Year: " << s.year
            << ", CGPA: " << s.cgpa << endl;
    }

    in.close();
    out.close();
    cout << "Records exported to students.txt\n";
}

void sortStudents() {
    vector<Student> students;
    string line;
    ifstream in("students.dat");
    while (getline(in, line)) {
        students.push_back(Student::fromCSV(line));
    }
    in.close();

    if (students.empty()) {
        cout << "No records to sort.\n";
        return;
    }

    int sortChoice;
    cout << "Sort by:\n1. Roll No\n2. Name\n3. CGPA\nEnter choice: ";
    cin >> sortChoice;

    switch (sortChoice) {
        case 1:
            sort(students.begin(), students.end(), [](Student a, Student b) { return a.rollNo < b.rollNo; });
            break;
        case 2:
            sort(students.begin(), students.end(), [](Student a, Student b) { return a.name < b.name; });
            break;
        case 3:
            sort(students.begin(), students.end(), [](Student a, Student b) { return a.cgpa > b.cgpa; });
            break;
        default:
            cout << "Invalid choice.\n";
            return;
    }

    cout << "\nSorted Records:\n";
    for (auto &s : students)
        s.display();
}

int main() {
    int choice;
    do {
        cout << "\n--- Student Record System ---\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search Student by Roll No\n";
        cout << "4. Update Student Record\n";
        cout << "5. Delete Student Record\n";
        cout << "6. Export to TXT\n";
        cout << "7. Sort Records\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exportToText(); break;
            case 7: sortStudents(); break;
            case 8: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 8);

    return 0;
}
