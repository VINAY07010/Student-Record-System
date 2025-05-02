#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    float marks;

    void input() {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        while (name.empty()) {
            cout << "Name cannot be empty. Re-enter: ";
            getline(cin, name);
        }
        cout << "Enter Marks: ";
        cin >> marks;
        while (marks < 0 || marks > 100) {
            cout << "Marks must be between 0 and 100. Re-enter: ";
            cin >> marks;
        }
    }

    void display() const {
        cout << "Roll No: " << rollNo << ", Name: " << name << ", Marks: " << marks << endl;
    }
};

void addStudent() {
    Student s;
    s.input();
    ofstream out("students.dat", ios::binary | ios::app);
    out.write((char*)&s, sizeof(s));
    out.close();
    cout << "Record added successfully.\n";
}

void displayAll() {
    Student s;
    ifstream in("students.dat", ios::binary);
    if (!in) {
        cout << "No records found.\n";
        return;
    }
    while (in.read((char*)&s, sizeof(s))) {
        s.display();
    }
    in.close();
}

void searchStudent() {
    int roll;
    bool found = false;
    Student s;
    cout << "Enter Roll No to search: ";
    cin >> roll;
    ifstream in("students.dat", ios::binary);
    while (in.read((char*)&s, sizeof(s))) {
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
    Student s;
    fstream file("students.dat", ios::binary | ios::in | ios::out);
    cout << "Enter Roll No to update: ";
    cin >> roll;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.rollNo == roll) {
            cout << "Old Record:\n";
            s.display();
            cout << "Enter New Details:\n";
            s.input();
            int pos = -1 * (int)sizeof(s);
            file.seekp(pos, ios::cur);
            file.write((char*)&s, sizeof(s));
            cout << "Record updated successfully.\n";
            found = true;
            break;
        }
    }
    file.close();
    if (!found)
        cout << "Student not found.\n";
}

void deleteStudent() {
    int roll;
    bool found = false;
    cout << "Enter Roll No to delete: ";
    cin >> roll;

    Student s;
    ifstream in("students.dat", ios::binary);
    ofstream out("temp.dat", ios::binary);

    while (in.read((char*)&s, sizeof(s))) {
        if (s.rollNo != roll)
            out.write((char*)&s, sizeof(s));
        else
            found = true;
    }
    in.close();
    out.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Record deleted successfully.\n";
    else
        cout << "Record not found.\n";
}

void exportToText() {
    Student s;
    ifstream in("students.dat", ios::binary);
    ofstream out("students.txt");

    while (in.read((char*)&s, sizeof(s))) {
        out << "Roll No: " << s.rollNo << ", Name: " << s.name << ", Marks: " << s.marks << endl;
    }

    in.close();
    out.close();
    cout << "Records exported to students.txt\n";
}

void sortStudents() {
    vector<Student> students;
    Student s;
    ifstream in("students.dat", ios::binary);
    while (in.read((char*)&s, sizeof(s))) {
        students.push_back(s);
    }
    in.close();

    if (students.empty()) {
        cout << "No records to sort.\n";
        return;
    }

    int sortChoice;
    cout << "Sort by:\n1. Roll No\n2. Name\n3. Marks\nEnter choice: ";
    cin >> sortChoice;

    switch (sortChoice) {
        case 1:
            sort(students.begin(), students.end(), [](Student a, Student b) { return a.rollNo < b.rollNo; });
            break;
        case 2:
            sort(students.begin(), students.end(), [](Student a, Student b) { return a.name < b.name; });
            break;
        case 3:
            sort(students.begin(), students.end(), [](Student a, Student b) { return a.marks > b.marks; });
            break;
        default:
            cout << "Invalid choice.\n";
            return;
    }

    cout << "\nSorted Records:\n";
    for (auto& s : students)
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
