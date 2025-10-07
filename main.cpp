#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_STUDENTS = 100;

struct Student {
    int id;
    char name[50];
    int age;
    double grade;
};

int studentCount = 0;
Student students[MAX_STUDENTS];

// Function prototypes
void loadStudentsFromFile(const char* filename);
void saveStudentsToFile(const char* filename);
bool addStudent();
bool updateStudent();
bool deleteStudent();
int getNextId();
void displayStudents();
void displayMenu();

int main() {
    loadStudentsFromFile("students.txt");

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(1000, '\n');  // Clear buffer

        switch (choice) {
            case 1:
                if (addStudent()) {
                    cout << "Student added successfully!" << endl;
                }
                break;
            case 2:
                updateStudent();
                break;
            case 3:
                deleteStudent();
                break;
            case 4:
                displayStudents();
                break;
            case 0:
                saveStudentsToFile("students.txt");
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
        cout << endl;
    } while (choice != 0);

    return 0;
}

// Load students from file (space-separated: id name age grade)
void loadStudentsFromFile(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File not found. Starting empty." << endl;
        return;
    }

    studentCount = 0;
    while (studentCount < MAX_STUDENTS && file >> students[studentCount].id
           >> students[studentCount].name >> students[studentCount].age
           >> students[studentCount].grade) {
        studentCount++;
    }

    file.close();
    cout << "Loaded " << studentCount << " students." << endl;
}

// Save students to file
void saveStudentsToFile(const char* filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        file << students[i].id << " " << students[i].name << " "
             << students[i].age << " " << students[i].grade << endl;
    }

    file.close();
    cout << "Saved " << studentCount << " students." << endl;
}

// Add student with basic validation
bool addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Maximum students reached." << endl;
        return false;
    }

    int id = getNextId();
    int age;
    double grade;
    char name[50];

    cout << "Enter name (single word): ";
    cin >> name;
    if (strlen(name) == 0) {
        cout << "Invalid name." << endl;
        return false;
    }

    cout << "Enter age (0-150): ";
    cin >> age;
    if (age < 0 || age > 150) {
        cout << "Invalid age." << endl;
        return false;
    }

    cout << "Enter grade (0.0-4.0): ";
    cin >> grade;
    if (grade < 0.0 || grade > 4.0) {
        cout << "Invalid grade." << endl;
        return false;
    }

    students[studentCount] = {id, "", age, grade};
    strcpy(students[studentCount].name, name);
    studentCount++;
    return true;
}

// Update student
bool updateStudent() {
    if (studentCount == 0) {
        cout << "No students." << endl;
        return false;
    }

    int id;
    cout << "Enter ID to update: ";
    cin >> id;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            cout << "Enter new name: ";
            cin >> students[i].name;

            int age;
            cout << "Enter new age: ";
            cin >> age;
            if (age >= 0 && age <= 150) students[i].age = age;

            double grade;
            cout << "Enter new grade: ";
            cin >> grade;
            if (grade >= 0.0 && grade <= 4.0) students[i].grade = grade;

            cout << "Updated." << endl;
            return true;
        }
    }
    cout << "Student not found." << endl;
    return false;
}

// Delete student
bool deleteStudent() {
    if (studentCount == 0) {
        cout << "No students." << endl;
        return false;
    }

    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            cout << "Deleted." << endl;
            return true;
        }
    }
    cout << "Student not found." << endl;
    return false;
}

// Get next ID
int getNextId() {
    if (studentCount == 0) return 1;
    int maxId = students[0].id;
    for (int i = 1; i < studentCount; i++) {
        if (students[i].id > maxId) maxId = students[i].id;
    }
    return maxId + 1;
}

// Display students
void displayStudents() {
    if (studentCount == 0) {
        cout << "No students." << endl;
        return;
    }

    cout << "ID | Name | Age | Grade" << endl;
    for (int i = 0; i < studentCount; i++) {
        cout << students[i].id << " | " << students[i].name << " | "
                  << students[i].age << " | " << students[i].grade << endl;
    }
}

// Display menu
void displayMenu() {
    cout << "=== Student System ===" << endl;
    cout << "1. Add" << endl;
    cout << "2. Update" << endl;
    cout << "3. Delete" << endl;
    cout << "4. Display" << endl;
    cout << "0. Exit" << endl;
}
