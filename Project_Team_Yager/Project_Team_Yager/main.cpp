#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <random>

#include "user.h"
#include "gui.h"

#define CMD_START 1
#define CMD_CREATE 2
#define CMD_STATS 3
#define CMD_SAVE 4
#define CMD_EXIT 0

using namespace std;

int main() {

    int command = CMD_EXIT;
    do {

        menu();
        cout << "\nCommand: ";
        cin >> command;
        cout << endl;

        switch (command) {

        case CMD_START: {

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string user_name;
            cout << "Enter your name: ";
            getline(cin, user_name);
            cout << endl;

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
                cout << endl;
            }

            auto end_time = chrono::steady_clock::now();
            auto exam_duration = chrono::duration_cast<chrono::seconds>(end_time - start_time).count();

            print_stats(correct_answers, exam.size(), exam_duration, per_category_correct);
            
            user currentUser;
            currentUser.name = user_name;
            currentUser.correct_answers = correct_answers;
            currentUser.total_questions = exam.size();
            currentUser.exam_duration_seconds = exam_duration;
            currentUser.per_category_correct = per_category_correct;
            users.push_back(currentUser);

            break;

        }

        case CMD_CREATE: {
            break;
        }
        case CMD_STATS: {

            if (users.empty()) {

                cout << "No user stats available yet.\n";

            }
            else {

                cout << left
                    << setw(20) << "Name"
                    << setw(12) << "Total Q"
                    << setw(12) << "Correct"
                    << setw(15) << "Duration(s)"
                    << setw(15) << "Percent"
                    << setw(10) << "Rating" << "\n";
                cout << string(20 + 12 + 12 + 15 + 15 + 10, '-') << "\n";

                for (user u : users) {
                    double percent_correct = (u.total_questions > 0) ? (100.0 * u.correct_answers / u.total_questions) : 0.0;
                    char rating = get_rating(percent_correct);

                    cout << left
                        << setw(20) << u.name
                        << setw(12) << u.total_questions
                        << setw(12) << u.correct_answers
                        << setw(15) << u.exam_duration_seconds
                        << setw(13) << fixed << setprecision(2) << percent_correct
                        << setw(10) << rating << "\n";
                }

            }

            cout << endl;

            break;
        }

        case CMD_SAVE: {

            ofstream outfile("users.txt");
            if (!outfile.is_open()) {
                cerr << "Error: Could not open file for writing." << endl;
                break;
            }
            for (const auto& u : users) {
                outfile << u.name << "\n";
                outfile << u.total_questions << " "
                    << u.correct_answers << " "
                    << u.exam_duration_seconds << "\n";

                for (size_t i = 0; i < u.per_category_correct.size(); i++) {
                    outfile << u.per_category_correct[i];
                    if (i < u.per_category_correct.size() - 1) {
                        outfile << " ";
                    }
                }
                outfile << "\n";
                outfile << "\n";
            }

            outfile.close();
            cout << "User data saved successfully to users.txt" << endl;
            break;

        }
        }

    } while (command != CMD_EXIT);

    return 0;
}