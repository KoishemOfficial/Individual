#pragma once

#include <string>

using namespace std;

#define GRADE_SIZE 10

struct Student {
    int id;
    string name;
    string surname;
    int grades[GRADE_SIZE];

    // Fill grades
    Student() {
        id = 0;
        name = "NULL";
        surname = "NULL";
        for (int i = 0; i < GRADE_SIZE; ++i) {
            grades[i] = -1;
        }
    }
};

extern Student* students;
extern int studentCount;

void ResetTemp();
void DisplayGrades();
void DisplayInitials();
void DisplayData();
void changeName();
void changeSurname();
void changeGrade();
void exportStudentToFile();
void importStudentFromFile();
void displayAllStudents();
void deleteStudentById();
void displayStudentByName();
void displayStudentBySurname();
void displayAllStudentsAlphabetically();
void displayTopStudents();
void replaceStudentById();