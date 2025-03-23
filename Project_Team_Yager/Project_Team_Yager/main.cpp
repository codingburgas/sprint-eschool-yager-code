#include <iostream>
#include <string>
#include <chrono>
#include <random>


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
            vector<unsigned> per_category_correct(CATEGORY_COUNT, 0);
            vector<question> exam = generate_exam();

            auto start_time = chrono::steady_clock::now();

            for (auto question : exam) {

                bool result = ask(question);
                if (result == true) {
                    correct_answers++;
                    per_category_correct[question.type]++;
                }
            }

            auto end_time = chrono::steady_clock::now();
            auto exam_duration = chrono::duration_cast<chrono::seconds>(end_time - start_time).count();

            print_stats(correct_answers, exam.size(), exam_duration, per_category_correct);
            
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