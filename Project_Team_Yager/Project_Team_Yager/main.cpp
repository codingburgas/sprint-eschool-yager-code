#include <iostream>
#include <string>

#include "gui.h"

#define CMD_START 1
#define CMD_CREATE 2
#define CMD_STATS 3
#define CMD_EXIT 0

using namespace std;

int main() {

    int command = CMD_EXIT;
    do {

        menu();
        cin >> command;
        cout << command;

        switch (command) {
        case CMD_START: {
            unsigned correct_answers = 0;
            vector<question> exam = generate_exam();
            for (auto question : exam) {
                bool result = ask(question);
                if (result == true) {
                    correct_answers++;
                }
            }
            break;
        }
        case CMD_CREATE: {
            break;
        }
        case CMD_STATS: {

            break;
        }
        }

    } while (command != CMD_EXIT);

    return 0;
}