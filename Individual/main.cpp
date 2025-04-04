#include "StudentHandler.h"
#include <iostream>

#define GRADE_SIZE 10

using namespace std;

bool running = true;

void quitApp() {
    running = false;
}

int main() {

    void (*operations[])() = { 
        changeName, changeSurname, changeGrade, exportStudentToFile, importStudentFromFile, displayAllStudents, displayStudentByName, displayStudentBySurname, deleteStudentById, displayAllStudentsAlphabetically, displayTopStudents
    };

    while (running) {
        int choice = -1;

        cout << "\nSelected person: ";
        DisplayData();
        cout << "\nChoose an operation: \n";
        cout << "0. Exit\n";
        cout << "1. changeName\n";
        cout << "2. changeSurname\n";
        cout << "3. changeGrade\n";
        cout << "4. exportStudentToFile\n";
        cout << "5. importStudentFromFile\n";
        cout << "6. displayAllStudents\n";
        cout << "7. displayStudentByName\n";
        cout << "8. displayStudentBySurname\n";
        cout << "9. deleteStudentById\n";
        cout << "10. displayAllStudentsAlphabetically\n";
        cout << "11. displayTopStudents\n";

        cin >> choice;

        if (choice == 0) {
            quitApp();
        }

        operations[choice - 1]();
    }

    return 0;
}
