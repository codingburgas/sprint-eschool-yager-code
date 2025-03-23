#include "gui.h"

void menu() {
    cout << "1. Start exam" << endl;
    cout << "2. Add question" << endl;
    cout << "3. Show stats" << endl;
    cout << "0. Exit" << endl;
}
enum type select_category() {

    cout << "Select a category:" << endl;
    for (int i = 0; i < CATEGORY_COUNT; i++) {
        cout << i + 1 << ". " << category_names[i] << endl;
    }

    int choice;
    cout << "Enter a number (1-" << CATEGORY_COUNT << "): ";
    cin >> choice;

    if (choice < 1 || choice > CATEGORY_COUNT) {
        cout << "Invalid choice. Defaulting to History.\n";
        return HISTORY;
    }

    return (enum type)(choice - 1);

}