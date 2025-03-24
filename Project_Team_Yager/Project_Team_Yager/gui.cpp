#include "gui.h"

void menu() {
    cout << "1. Start exam" << endl;
    cout << "2. Add question" << endl;
    cout << "3. Show stats" << endl;
    cout << "4. Save data" << endl;
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

void print_stats(
    unsigned correct_answers,
    unsigned total_questions,
    long exam_duration_seconds,
    vector<unsigned> per_category_correct) {

    double percent_correct = (total_questions > 0) ? (100.0 * correct_answers / total_questions) : 0.0;
    char rating = get_rating(percent_correct);

    cout << "\n--- Exam Statistics ---\n";

    cout << "Total exam time: " << exam_duration_seconds << " seconds\n";

    cout << "Questions answered: " << total_questions << "\n";
    cout << "Correct answers: " << correct_answers << "\n";
    cout << fixed << setprecision(2);
    cout << "Percentage correct: " << percent_correct << "%\n";
    cout << "Rating: " << rating << "\n\n";

    cout << "Breakdown per question type:\n";

    for (size_t i = 0; i < CATEGORY_COUNT; i++) {
        double cat_percent = 100.0 * per_category_correct[i] / 4;
        cout << category_names[i] << ": "
            << per_category_correct[i] << "/" << 4
            << " (" << cat_percent << "% correct)\n";
    }

    cout << "-----------------------\n\n\n";

}