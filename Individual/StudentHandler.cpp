#include "StudentHandler.h"
#include <iostream>
#include <fstream>

Student temp;

using namespace std;

void ResetTemp() {
    temp.id = 0;
    temp.name = "NULL";
    temp.surname = "NULL";
    for (int i = 0; i < GRADE_SIZE; ++i) {
        temp.grades[i] = -1;
    }
}

void DisplayGrades() {
    for (int i = 0; i < GRADE_SIZE; i++) {
        cout << "[" << i << "] " << temp.grades[i] << " ";
    }
}

void DisplayInitials() {
    cout << temp.name << ' ' << temp.surname;
}

void DisplayData() {
    cout << "ID: " << temp.id << " Name: " << temp.name << " Surname: " << temp.surname << " | Grades: ";
    DisplayGrades();
    cout << '\n';
}

void changeName() {
    cout << "Enter a new name for: " << temp.name << '\n';
    cin >> temp.name;
}

void changeSurname() {
    cout << "Enter a new surname for: " << temp.surname << '\n';
    cin >> temp.surname;
}

void changeGrade() {
    int index = 0, new_grade = 0;

    DisplayInitials();
    cout << " grades:\n";
    DisplayGrades();

    cout << "\nEnter an index: ";
    cin >> index;
    cout << "\nEnter a new grade: ";
    cin >> new_grade;
    cout << '\n';

    if (new_grade > 12) {
        new_grade = 12;
    }

    if (index >= 0 && index < GRADE_SIZE) {
        temp.grades[index] = new_grade;
    }
    else {
        cout << "[ERROR] Invalid index. Expected value: 0-" << GRADE_SIZE - 1 << ".\n";
    }
}

void exportStudentToFile() {
    // when exporting a student an id will be assigned automatically
    ifstream file("students.txt");

    int nextId = 0;
    if (file) {
        int id;
        string name, surname;
        int grades[GRADE_SIZE];
        while (file >> id >> name >> surname) {
            for (int i = 0; i < GRADE_SIZE; ++i) {
                file >> grades[i];
            }
            nextId = max(nextId, id + 1);
        }
    }

    file.close();

    temp.id = nextId;

    ofstream outFile("students.txt", ios::app);
    if (!outFile) {
        cout << "[ERROR] Couldn't open the file.\n";
        return;
    }

    outFile << temp.id << " " << temp.name << " " << temp.surname << " ";
    for (int i = 0; i < GRADE_SIZE; ++i) {
        outFile << temp.grades[i] << " ";
    }
    outFile << "\n";

    outFile.close();
    cout << "Student exported successfully with ID: " << temp.id << "\n";
    ResetTemp();
}

void importStudentFromFile() {
    int searchId = -1;
    cout << "Enter an ID: ";
    cin >> searchId;
    cout << '\n';

    ifstream file("students.txt");

    if (!file) {
        cout << "[ERROR] Couldn't open the file.\n";
        return;
    }

    int id;
    string name, surname;
    int grades[GRADE_SIZE];

    while (file >> id >> name >> surname) {
        for (int i = 0; i < GRADE_SIZE; ++i) {
            file >> grades[i];
        }

        if (id == searchId) {
            temp.id = id;
            temp.name = name;
            temp.surname = surname;
            for (int i = 0; i < GRADE_SIZE; ++i) {
                temp.grades[i] = grades[i];
            }

            file.close();
            cout << "Student imported successfully.\n";
            return;
        }
    }

    file.close();
    cout << "[ERROR] Student not found with ID: " << searchId << "\n";
}

void displayAllStudents() {
    ifstream file("students.txt");

    if (!file) {
        cout << "[ERROR] Couldn't open the file.\n";
        return;
    }

    int id;
    string name, surname;
    int grades[GRADE_SIZE];

    cout << "\nList of all students:\n\n";

    while (file >> id >> name >> surname) {
        cout << "ID: " << id << " Name: " << name << " Surname: " << surname << " | Grades: ";
        for (int i = 0; i < GRADE_SIZE; ++i) {
            file >> grades[i];
            cout << grades[i] << " ";
        }
        cout << "\n";
    }

    file.close();
}

void deleteStudentById() {
    // creates a temp.txt file to copy data from students.txt, and delete the selected student by ID, then temp.txt is renamed to students.txt, while original file is being deleted
    int idToDelete = -1;
    cout << "Enter an ID: ";
    cin >> idToDelete;
    cout << '\n';

    ifstream file("students.txt");

    if (!file) {
        cout << "[ERROR] Couldn't open the file.\n";
        return;
    }

    ofstream tempFile("temp.txt");

    if (!tempFile) {
        cout << "[ERROR] Couldn't create a temporary file.\n";
        file.close();
        return;
    }

    int id;
    string name, surname;
    int grades[GRADE_SIZE];

    bool found = false;

    while (file >> id >> name >> surname) {
        bool skipStudent = false;

        for (int i = 0; i < GRADE_SIZE; ++i) {
            file >> grades[i];
        }

        if (id == idToDelete) {
            found = true;
            continue;
        }

        tempFile << id << " " << name << " " << surname << " ";
        for (int i = 0; i < GRADE_SIZE; ++i) {
            tempFile << grades[i] << " ";
        }
        tempFile << "\n";
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("students.txt");
        rename("temp.txt", "students.txt");
        cout << "Student with ID " << idToDelete << " was successfully deleted.\n";
    }
    else {
        remove("temp.txt");
        cout << "[ERROR] Student with ID " << idToDelete << " not found.\n";
    }
}

void displayStudentByName() {
    string searchName;
    cout << "Enter name to search for: ";
    cin >> searchName;

    ifstream file("students.txt");

    if (!file) {
        cout << "[ERROR] Couldn't open the file.\n";
        return;
    }

    int id;
    string name, surname;
    int grades[GRADE_SIZE];
    bool found = false;

    cout << "Students with the name " << searchName << ":\n";

    while (file >> id >> name >> surname) {
        for (int i = 0; i < GRADE_SIZE; ++i) {
            file >> grades[i];
        }

        if (name == searchName) {
            found = true;
            cout << "ID: " << id << " Name: " << name << " Surname: " << surname << " | Grades: ";
            for (int i = 0; i < GRADE_SIZE; ++i) {
                cout << grades[i] << " ";
            }
            cout << "\n";
        }
    }

    if (!found) {
        cout << "[ERROR] No student found with the name " << searchName << ".\n";
    }

    file.close();
}

void displayStudentBySurname() {
    string searchSurname;
    cout << "Enter surname to search for: ";
    cin >> searchSurname;

    ifstream file("students.txt");

    if (!file) {
        cout << "[ERROR] Couldn't open the file.\n";
        return;
    }

    int id;
    string name, surname;
    int grades[GRADE_SIZE];
    bool found = false;

    cout << "Students with the surname " << searchSurname << ":\n";

    while (file >> id >> name >> surname) {
        for (int i = 0; i < GRADE_SIZE; ++i) {
            file >> grades[i];
        }

        if (surname == searchSurname) {
            found = true;
            cout << "ID: " << id << " Name: " << name << " Surname: " << surname << " | Grades: ";
            for (int i = 0; i < GRADE_SIZE; ++i) {
                cout << grades[i] << " ";
            }
            cout << "\n";
        }
    }

    if (!found) {
        cout << "[ERROR] No student found with the surname " << searchSurname << ".\n";
    }

    file.close();
}

void displayAllStudentsAlphabetically() {
    ifstream file("students.txt");

    if (!file) {
        cout << "[ERROR] Couldn't open the file.\n";
        return;
    }

    int studentsCount = 0;
    int tempId;
    string tempName, tempSurname;
    int tempGrades[GRADE_SIZE];

    while (file >> tempId >> tempName >> tempSurname) {
        for (int i = 0; i < GRADE_SIZE; ++i) {
            file >> tempGrades[i];
        }
        studentsCount++;
    }

    file.clear();
    file.seekg(0, ios::beg);

    Student* students = new Student[studentsCount];
    int index = 0;

    while (file >> students[index].id >> students[index].name >> students[index].surname) {
        for (int i = 0; i < GRADE_SIZE; ++i) {
            file >> students[index].grades[i];
        }
        index++;
    }

    file.close();

    for (int i = 0; i < studentsCount - 1; ++i) {
        for (int j = i + 1; j < studentsCount; ++j) {
            if (students[i].name > students[j].name) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    cout << "\nList of all students sorted by name:\n\n";
    for (int i = 0; i < studentsCount; ++i) {
        cout << "ID: " << students[i].id << " Name: " << students[i].name << " Surname: " << students[i].surname << " | Grades: ";
        for (int j = 0; j < GRADE_SIZE; ++j) {
            cout << students[i].grades[j] << " ";
        }
        cout << "\n";
    }

    delete[] students;
}

void displayTopStudents() {
    ifstream file("students.txt");

    if (!file) {
        cout << "[ERROR] Couldn't open the file.\n";
        return;
    }

    int id;
    string name, surname;
    int grades[GRADE_SIZE];

    cout << "\nList of top students (average grade 10+):\n\n";

    while (file >> id >> name >> surname) {
        double average = 0;
        for (int i = 0; i < GRADE_SIZE; ++i) {
            file >> grades[i];
            average += grades[i];
        }
        average /= GRADE_SIZE;

        if (average >= 10) {
            cout << "ID: " << id << " Name: " << name << " Surname: " << surname << " | Average grade: " << average << "\n";
        }
        file.ignore();
    }

    file.close();
}

void replaceStudentById() {
    int searchId = -1;

    cout << "Enter the ID of the student to replace: ";
    cin >> searchId;
    cout << '\n';

    ifstream file("students.txt");

    if (!file) {
        cout << "[ERROR] Couldn't open the file.\n";
        return;
    }

    ofstream tempFile("temp.txt");

    if (!tempFile) {
        cout << "[ERROR] Couldn't create a temporary file.\n";
        file.close();
        return;
    }

    int id;
    string name, surname;
    int grades[GRADE_SIZE];
    bool found = false;

    while (file >> id >> name >> surname) {
        for (int i = 0; i < GRADE_SIZE; ++i) {
            file >> grades[i];
        }

        if (id == searchId) {
            found = true;

            tempFile << searchId << " " << temp.name << " " << temp.surname << " ";
            for (int i = 0; i < GRADE_SIZE; ++i) {
                tempFile << temp.grades[i] << " ";
            }
            tempFile << "\n";
        }
        else {
            tempFile << id << " " << name << " " << surname << " ";
            for (int i = 0; i < GRADE_SIZE; ++i) {
                tempFile << grades[i] << " ";
            }
            tempFile << "\n";
        }
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("students.txt");
        rename("temp.txt", "students.txt");
        cout << "Student with ID " << searchId << " was successfully replaced.\n";
    }
    else {
        remove("temp.txt");
        cout << "[ERROR] Student with ID " << searchId << " not found.\n";
    }
}