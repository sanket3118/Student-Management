#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib> // System commands ????

using namespace std;

class Student {
private:
    int rollNo;
    string name;
    string course;
    float marks;

public:
    void getData() {
        cout << "\n--- Admin: Enter Student Details ---" << endl;
        cout << "Enter Roll Number: ";
        cin >> rollNo;
        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);
        cout << "Enter Course Name: ";
        getline(cin, course);
        cout << "Enter Marks (out of 100): ";
        cin >> marks;
    }

    int getRollNo() const { return rollNo; }
    string getName() const { return name; }
    string getCourse() const { return course; }
    float getMarks() const { return marks; }
};

// Dev-C++ ????? ?????????? ?? ?????? ? ??????????????? ???? ????????? ?????? ????
void initializeDefaultData() {
    ifstream checkFile("students.txt");
    if (checkFile) {
        checkFile.close();
        return; // ???? ???????? ???? ?? ?????? ???? ??????? ????
    }

    ofstream outFile("students.txt");
    if (!outFile) return;

    // ? ??????????????? ???? ????
    outFile << "101|Amit Sharma|Computer Engg|85.50\n";
    outFile << "102|Rahul Patil|IT Engg|78.00\n";
    outFile << "103|Priya Deshmukh|Data Science|92.30\n";
    outFile << "104|Sneha Joshi|AI & ML|69.50\n";
    outFile << "105|Vikas Verma|Software Engg|81.20\n";

    outFile.close();
}

void addStudent() {
    Student s;
    s.getData();

    ofstream outFile("students.txt", ios::app);
    if (!outFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    outFile << s.getRollNo() << "|" << s.getName() << "|" << s.getCourse() << "|" << s.getMarks() << "\n";
    outFile.close();
    cout << "\n? Student record with marks added successfully!" << endl;
}

void displayStudents() {
    ifstream inFile("students.txt");
    if (!inFile) {
        cout << "\n?? No records found! Please add student first." << endl;
        return;
    }

    string line;
    cout << "\n============================================================\n";
    cout << left << setw(10) << "Roll No" << setw(20) << "Name" << setw(15) << "Course" << setw(10) << "Marks" << endl;
    cout << "============================================================\n";

    while (getline(inFile, line)) {
        if (line.empty()) continue;
        
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        int rNo = atoi(line.substr(0, pos1).c_str());
        string sName = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string sCourse = line.substr(pos2 + 1, pos3 - pos2 - 1);
        float sMarks = atof(line.substr(pos3 + 1).c_str());

        cout << left << setw(10) << rNo 
             << setw(20) << sName 
             << setw(15) << sCourse 
             << setw(10) << fixed << setprecision(2) << sMarks << endl;
    }
    cout << "============================================================\n";
    inFile.close();
}

void updateStudent() {
    int targetRoll;
    cout << "\nEnter Roll Number to update details/marks: ";
    cin >> targetRoll;

    ifstream inFile("students.txt");
    ofstream tempFile("temp.txt");
    
    if (!inFile) {
        cout << "File could not be opened!" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        int rNo = atoi(line.substr(0, pos1).c_str());
        string sName = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string sCourse = line.substr(pos2 + 1, pos3 - pos2 - 1);
        float sMarks = atof(line.substr(pos3 + 1).c_str());

        if (rNo == targetRoll) {
            found = true;
            cout << "\nCurrent Details - Name: " << sName << ", Course: " << sCourse << ", Marks: " << sMarks << endl;
            
            cin.ignore();
            cout << "Enter New Name: ";
            getline(cin, sName);
            cout << "Enter New Course: ";
            getline(cin, sCourse);
            cout << "Enter New Marks: ";
            cin >> sMarks;
        }
        
        tempFile << rNo << "|" << sName << "|" << sCourse << "|" << sMarks << "\n";
    }

    inFile.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) cout << "\n? Record updated successfully!" << endl;
    else cout << "\n? Record not found!" << endl;
}

void deleteStudent() {
    int targetRoll;
    cout << "\nEnter Roll Number to delete: ";
    cin >> targetRoll;

    ifstream inFile("students.txt");
    ofstream tempFile("temp.txt");

    if (!inFile) {
        cout << "File could not be opened!" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        size_t pos1 = line.find('|');
        int rNo = atoi(line.substr(0, pos1).c_str());

        if (rNo == targetRoll) {
            found = true;
            continue;
        }
        tempFile << line << "\n";
    }

    inFile.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) cout << "\n? Record deleted successfully!" << endl;
    else cout << "\n? Record not found!" << endl;
}

int main() {
    initializeDefaultData();

    int choice;
    do {
        cout << "\n?? --- STUDENT MANAGEMENT SYSTEM --- ??";
        cout << "\n1. Admin: Add New Student & Marks";
        cout << "\n2. Display All Student Records (Pre-loaded Data)";
        cout << "\n3. Update Student/Marks Record";
        cout << "\n4. Delete Student Record";
        cout << "\n5. Exit";
        cout << "\nEnter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: cout << "\nExiting... Thank you!" << endl; break;
            default: cout << "\n? Invalid choice! Enter 1-5." << endl;
        }
    } while (choice != 5);

    return 0;
}

