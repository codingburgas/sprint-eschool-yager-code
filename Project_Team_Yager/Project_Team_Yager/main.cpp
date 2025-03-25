#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <random>
#include <climits>

#include "user.h"
#include "question.h"
#include "gui.h"

#define CMD_START 1
#define CMD_CREATE 2
#define CMD_STATS 3
#define CMD_SUMMARY 4
#define CMD_SAVE 5
#define CMD_EXIT 0

using namespace std;

int main() {

    vector<user> users = loadUsersFromFile("users.txt");
    vector<question> questions = loadQuestionsFromFile("questions.txt");


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
            vector<question> exam = generate_exam(questions);

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

            question newQuestion;

            // Ensure the input buffer is clear
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Prompt for question text
            cout << "Enter question text: ";
            getline(cin, newQuestion.text);

            
            cout << "Enter correct answer: ";
            getline(cin, newQuestion.answer);

            
            cout << "Enter wrong answer 1: ";
            getline(cin, newQuestion.wrong1);

            
            cout << "Enter wrong answer 2: ";
            getline(cin, newQuestion.wrong2);

            
            cout << "Enter wrong answer 3: ";
            getline(cin, newQuestion.wrong3);

            cout << "\nAvailable categories:" << endl;
            for (int i = 0; i < CATEGORY_COUNT; i++) {
                cout << i << " - " << category_names[i] << endl;
            }

            int typeInput = -1;
            cout << "Enter question type (number from 0 to " << (CATEGORY_COUNT - 1) << "): ";
            while (!(cin >> typeInput) || typeInput < 0 || typeInput >= CATEGORY_COUNT) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid input. Please enter a number between 0 and " << (CATEGORY_COUNT - 1) << ": ";
            }
            newQuestion.type = static_cast<type>(typeInput);

            // Clear the newline left in the input stream after numeric input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Add the new question to the global vector
            questions.push_back(newQuestion);
            cout << "New question added successfully." << endl;

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

        case CMD_SUMMARY: {
            if (users.empty()) {
                cout << "No user data available.\n";
                break;
            }

            double totalPercentage = 0.0;
            double totalTime = 0.0;

            double bestOverall = -1.0;
            string bestOverallUser;
            double worstOverall = 101.0;
            string worstOverallUser;

            long bestTime = LONG_MAX;   // best: minimum exam duration
            string bestTimeUser;
            long worstTime = 0;         // worst: maximum exam duration
            string worstTimeUser;

            // Process overall metrics from each user's data.
            for (const auto& u : users) {
                double userPercentage = (u.total_questions > 0) 
                    ? (100.0 * u.correct_answers / u.total_questions) 
                    : 0.0;
                totalPercentage += userPercentage;
                totalTime += u.exam_duration_seconds;

                if (userPercentage > bestOverall) {
                    bestOverall = userPercentage;
                    bestOverallUser = u.name;
                }
                if (userPercentage < worstOverall) {
                    worstOverall = userPercentage;
                    worstOverallUser = u.name;
                }

                if (u.exam_duration_seconds < bestTime) {
                    bestTime = u.exam_duration_seconds;
                    bestTimeUser = u.name;
                }
                if (u.exam_duration_seconds > worstTime) {
                    worstTime = u.exam_duration_seconds;
                    worstTimeUser = u.name;
                }

                
            }

            double avgPercentage = totalPercentage / users.size();
            double avgTime = totalTime / users.size();

            // Print a overal results.

            cout << left << setw(30) << "Metric"
                << setw(20) << "Value"
                << setw(30) << "User/Category" << "\n";
            cout << string(80, '-') << "\n";

            cout << left << setw(30) << "Average Result (%)"
                << setw(20) << fixed << setprecision(2) << avgPercentage
                << setw(30) << "" << "\n";

            cout << left << setw(30) << "Best Result (%)"
                << setw(20) << fixed << setprecision(2) << bestOverall
                << setw(30) << bestOverallUser << "\n";

            cout << left << setw(30) << "Worst Result (%)"
                << setw(20) << fixed << setprecision(2) << worstOverall
                << setw(30) << worstOverallUser << "\n";

            cout << left << setw(30) << "Average Time (sec)"
                << setw(20) << fixed << setprecision(2) << avgTime
                << setw(30) << "" << "\n";

            cout << left << setw(30) << "Best Time (sec)"
                << setw(20) << bestTime
                << setw(30) << bestTimeUser << "\n";

            cout << left << setw(30) << "Worst Time (sec)"
                << setw(20) << worstTime
                << setw(30) << worstTimeUser << "\n\n";
            
            // Now print per-category summary.
            cout << left << setw(15) << "Category"
                << setw(20) << "Average (%)"
                << setw(20) << "Best (%)"
                << setw(20) << "Worst (%)"
                << "Best/Worst Users" << "\n";
            cout << string(90, '-') << "\n";

            // Iterate over each category.
            for (int i = 0; i < CATEGORY_COUNT; i++) {
                double sum = 0.0;
                double best = -1.0;
                double worst = 101.0;
                string bestUser, worstUser;

                // For each user, compute the category percentage (assuming 4 questions per category).
                for (const auto& u : users) {
                    double catPercentage = 100.0 * u.per_category_correct[i] / 4;
                    sum += catPercentage;
                    if (catPercentage > best) {
                        best = catPercentage;
                        bestUser = u.name;
                    }
                    if (catPercentage < worst) {
                        worst = catPercentage;
                        worstUser = u.name;
                    }
                }
                double avg = sum / users.size();

                cout << left << setw(15) << category_names[i]
                    << setw(20) << fixed << setprecision(2) << avg
                    << setw(20) << fixed << setprecision(2) << best
                    << setw(20) << fixed << setprecision(2) << worst
                    << bestUser << " / " << worstUser << "\n";
            }

            break;
        }

        case CMD_SAVE: {

            // Saving the users to file

            ofstream outfile("users.txt");
            if (!outfile.is_open()) {
                cout << "Error: Could not open file for writing." << endl;
                break;
            }
            for (auto u : users) {
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
            

            // Saving the questions to file

            ofstream qFile("questions.txt");
            if (!qFile.is_open()) {
                cout << "Error: Could not open file for writing questions." << endl;
                break;
            }

            for (auto q : questions) {
                qFile << q.text << "\n";
                qFile << q.answer << "\n";
                qFile << q.wrong1 << "\n";
                qFile << q.wrong2 << "\n";
                qFile << q.wrong3 << "\n";
                qFile << static_cast<int>(q.type) << "\n";
                qFile << "\n";
            }

            qFile.close();
            cout << "Questions saved successfully to questions.txt." << endl;

            break;

        }
        }

    } while (command != CMD_EXIT);

    return 0;
}