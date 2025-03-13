#ifndef QUESTION_H
#define QUESTION_H

#include <string>
#include <vector>
using namespace std;

class Question {
private:
    string text;
    vector<string> options;
    int correctOption;
    int categoryId;
    int points;

public:
    Question();
    Question(const string& text, const vector<string>& options,
        int correctOption, int categoryId, int points = 1);

    string getText() const;
    vector<string> getOptions() const;
    int getCorrectOption() const;
    int getCategoryId() const;
    int getPoints() const;
    bool isCorrect(int selectedOption) const;
};

#endif