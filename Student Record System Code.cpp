#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Student {
    int id;
    string name;
    float gpa;
    Student* next;
};

class StudentList {
private:
    Student* head;
public:
    StudentList() : head(nullptr) {}
    ~StudentList();

    void addStudent(int id, const string& name, float gpa);
    bool removeStudent(int id);
    Student* findStudent(int id);
    void displayAll();
    bool updateStudent(int id, const string& newName, float newGpa);
    bool updateStudentName(int id, const string& newName);
    bool updateStudentGpa(int id, float newGpa);
    void sortByGpa();
    int countStudents();
};

// Destructor
StudentList::~StudentList() {
    Student* current = head;
    while (current) {
        Student* temp = current;
        current = current->next;
        delete temp;
    }
}

// Add Student
void StudentList::addStudent(int id, const string& name, float gpa) {
    Student* newStudent = new Student{id, name, gpa, head};
    head = newStudent;
}

// Remove Student
bool StudentList::removeStudent(int id) {
    Student* current = head;
    Student* prev = nullptr;
    while (current) {
        if (current->id == id) {
            if (prev) prev->next = current->next;
            else head = current->next;
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

// Find Student
Student* StudentList::findStudent(int id) {
    Student* current = head;
    while (current) {
        if (current->id == id) return current;
        current = current->next;
    }
    return nullptr;
}

// Display All Students
void StudentList::displayAll() {
    Student* current = head;
    if (!current) {
        cout << "No student records found.\n";
        return;
    }
    cout << "\nID\tName\tGPA" << endl;
    while (current) {
        cout << current->id << "\t" << current->name << "\t" << current->gpa << endl;
        current = current->next;
    }
}

// Update Full Info
bool StudentList::updateStudent(int id, const string& newName, float newGpa) {
    Student* s = findStudent(id);
    if (s) {
        s->name = newName;
        s->gpa = newGpa;
        return true;
    }
    return false;
}

// Update Only Name
bool StudentList::updateStudentName(int id, const string& newName) {
    Student* s = findStudent(id);
    if (s) {
        s->name = newName;
        return true;
    }
    return false;
}

// Update Only GPA
bool StudentList::updateStudentGpa(int id, float newGpa) {
    Student* s = findStudent(id);
    if (s) {
        s->gpa = newGpa;
        return true;
    }
    return false;
}

// Sort Students by GPA
void StudentList::sortByGpa() {
    if (!head || !head->next) return;
    for (Student* i = head; i; i = i->next) {
        for (Student* j = i->next; j; j = j->next) {
            if (i->gpa > j->gpa) {
                swap(i->id, j->id);
                swap(i->name, j->name);
                swap(i->gpa, j->gpa);
            }
        }
    }
    cout << "Students sorted by GPA.\n";
}

// Count Students
int StudentList::countStudents() {
    int count = 0;
    Student* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

// Main Program
int main() {
    StudentList sl;
    int choice;

    do {
        cout << "\n======= Student Record System =======" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Remove Student" << endl;
        cout << "3. Find Student by ID" << endl;
        cout << "4. Display All Students" << endl;
        cout << "5. Update Student Info" << endl;
        cout << "6. Sort Students by GPA" << endl;
        cout << "7. Count Total Students" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Input validation
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number between 0 and 7.\n";
            choice = -1;
            continue;
        }

        if (choice == 1) {
            int id;
            string name;
            float gpa;

            cout << "Enter ID: ";
            cin >> id;

            Student* existing = sl.findStudent(id);
            if (existing) {
                cout << "Error: Student with ID " << id << " already exists: "
                     << existing->name << ", GPA: " << existing->gpa << endl;
                cout << "Press 1 to update, 0 to cancel: ";
                int opt;
                cin >> opt;
                if (opt == 1) {
                    cout << "Choose what to update:\n";
                    cout << "1. Name\n2. GPA\n3. Both\nEnter choice: ";
                    int updateChoice;
                    cin >> updateChoice;
                    if (updateChoice == 1) {
                        cout << "Enter new Name: "; cin >> ws; getline(cin, name);
                        sl.updateStudentName(id, name);
                        cout << "Name updated.\n";
                    } else if (updateChoice == 2) {
                        cout << "Enter new GPA: "; cin >> gpa;
                        sl.updateStudentGpa(id, gpa);
                        cout << "GPA updated.\n";
                    } else if (updateChoice == 3) {
                        cout << "Enter new Name: "; cin >> ws; getline(cin, name);
                        cout << "Enter new GPA: "; cin >> gpa;
                        sl.updateStudent(id, name, gpa);
                        cout << "Name and GPA updated.\n";
                    } else {
                        cout << "Invalid update option.\n";
                    }
                } else {
                    cout << "Operation cancelled.\n";
                }
            } else {
                cout << "Enter Name: "; cin >> ws; getline(cin, name);
                cout << "Enter GPA: "; cin >> gpa;
                sl.addStudent(id, name, gpa);
                cout << "Student added successfully.\n";
            }

        } else if (choice == 2) {
            int id;
            cout << "Enter ID to remove: "; cin >> id;
            if (sl.removeStudent(id)) cout << "Student removed successfully.\n";
            else cout << "Student not found.\n";
        } else if (choice == 3) {
            int id;
            cout << "Enter ID to find: "; cin >> id;
            Student* s = sl.findStudent(id);
            if (s) cout << "Found: " << s->id << ", " << s->name << ", " << s->gpa << endl;
            else cout << "Student not found.\n";
        } else if (choice == 4) {
            sl.displayAll();
        } else if (choice == 5) {
            int id;
            string name;
            float gpa;
            cout << "Enter ID to update: "; cin >> id;
            Student* s = sl.findStudent(id);
            if (!s) {
                cout << "Student not found.\n";
            } else {
                cout << "Choose what to update:\n";
                cout << "1. Name\n2. GPA\n3. Both\nEnter choice: ";
                int updateChoice;
                cin >> updateChoice;
                if (updateChoice == 1) {
                    cout << "Enter new Name: "; cin >> ws; getline(cin, name);
                    sl.updateStudentName(id, name);
                    cout << "Name updated.\n";
                } else if (updateChoice == 2) {
                    cout << "Enter new GPA: "; cin >> gpa;
                    sl.updateStudentGpa(id, gpa);
                    cout << "GPA updated.\n";
                } else if (updateChoice == 3) {
                    cout << "Enter new Name: "; cin >> ws; getline(cin, name);
                    cout << "Enter new GPA: "; cin >> gpa;
                    sl.updateStudent(id, name, gpa);
                    cout << "Name and GPA updated.\n";
                } else {
                    cout << "Invalid update option.\n";
                }
            }
        } else if (choice == 6) {
            sl.sortByGpa();
        } else if (choice == 7) {
            cout << "Total students: " << sl.countStudents() << endl;
        } else if (choice == 0) {
            cout << "Exiting the program. Goodbye!\n";
        } else {
            cout << "Invalid choice. Please select from 0 to 7.\n";
        }

    } while (choice != 0);

    return 0;
}
