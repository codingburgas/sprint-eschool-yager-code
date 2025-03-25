#include "question.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept>


vector<question> filterQuestionsByCategory(vector<question> allQuestions, int category) {

    vector<question> filteredQuestions;

    for (auto q : allQuestions) {
        if (q.type == category) {
            filteredQuestions.push_back(q);
        }
    }

    return filteredQuestions;

}

vector<question> selectRandomSubset(vector<question> questionsList, size_t count, mt19937 rng) {

    if (questionsList.size() < count) {
        throw runtime_error("Not enough questions in the category to select the requested number.");
    }

    vector<question> shuffledQuestions = questionsList;
    shuffle(shuffledQuestions.begin(), shuffledQuestions.end(), rng);
    vector<question> subset(shuffledQuestions.begin(), shuffledQuestions.begin() + count);

    return subset;

}

vector<question> generate_exam(vector<question> questions) {

    vector<question> exam;
    random_device rd;
    mt19937 rng(rd());

    for (int category = 0; category < CATEGORY_COUNT; ++category) {

        vector<question> categoryQuestions = filterQuestionsByCategory(questions, category);

        if (categoryQuestions.size() < 4) {
            throw runtime_error("Not enough questions in category: " + category_names[category]);
        }

        vector<question> selectedQuestions = selectRandomSubset(categoryQuestions, 4, rng);
        exam.insert(exam.end(), selectedQuestions.begin(), selectedQuestions.end());

    }

    shuffle(exam.begin(), exam.end(), rng);
    return exam;

}
vector<question> loadQuestionsFromFile(string filename) {

    vector<question> loadedQuestions;

    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Error: Could not open file " << filename << " for reading.\n";
        return loadedQuestions;
    }

    string line;
    while (getline(infile, line)) {
        // Skip empty lines
        if (line.empty())
            continue;

        // Read the question text
        string text = line;

        // Read correct answer
        if (!getline(infile, line)) break;
        string answer = line;

        // Read wrong answer 1
        if (!getline(infile, line)) break;
        string wrong1 = line;

        // Read wrong answer 2
        if (!getline(infile, line)) break;
        string wrong2 = line;

        // Read wrong answer 3
        if (!getline(infile, line)) break;
        string wrong3 = line;

        // Read category type as integer
        if (!getline(infile, line)) break;
        int typeInt = stoi(line);
        enum type cat = static_cast<type>(typeInt);

        // Create a question and add it to the vector
        question q{ text, answer, wrong1, wrong2, wrong3, cat };
        loadedQuestions.push_back(q);

        // Read the blank separator line
        getline(infile, line);
    }

    infile.close();
    return loadedQuestions;
}

bool ask(question question) {

    vector<string> options = { question.answer, question.wrong1, question.wrong2, question.wrong3 };
    random_device rd;
    mt19937 rng(rd());
    shuffle(options.begin(), options.end(), rng);

    cout << question.text << endl;
    for (int i = 0; i < options.size(); i++) {
        cout << (i + 1) << ". " << options[i] << endl;
    }

    int userInput = 0;

    while (true) {
        cout << "\nEnter your answer (1-4): ";
        cin >> userInput;

        if (cin.fail() || userInput < 1 || userInput > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
        }
        else {
            break;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    return options[userInput - 1] == question.answer;
}