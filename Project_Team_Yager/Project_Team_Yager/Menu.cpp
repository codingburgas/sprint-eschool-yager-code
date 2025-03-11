#include "Menu.h"
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;


void Menu::showMainMenu() {
    cout << "==== ELECTRONIC SCHOOL SYSTEM ====" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "0. Exit" << endl;
    cout << "==================================" << endl;
    cout << "Enter your choice: ";
}

void Menu::showStudentMenu() {
    cout << "==== STUDENT MENU ====" << endl;
    cout << "Welcome, " << currentUser->getUsername() << "!" << endl;
    cout << "1. Take a Test" << endl;
    cout << "2. View Statistics" << endl;
    cout << "9. Logout" << endl;
    cout << "0. Exit" << endl;
    cout << "======================" << endl;
    cout << "Enter your choice: ";
}

void Menu::showTeacherMenu() {
    cout << "==== TEACHER MENU ====" << endl;
    cout << "Welcome, " << currentUser->getUsername() << "!" << endl;
    cout << "1. Create a Test" << endl;
    cout << "2. Add Question" << endl;
    cout << "3. Add Category" << endl;
    cout << "4. View Statistics" << endl;
    cout << "9. Logout" << endl;
    cout << "0. Exit" << endl;
    cout << "======================" << endl;
    cout << "Enter your choice: ";
}
