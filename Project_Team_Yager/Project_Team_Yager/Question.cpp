#include "Question.h"
using namespace std;

Question::Question() : correctOption(0), categoryId(0), points(1) {}

Question::Question(const string& text, const vector<string>& options,
    int correctOption, int categoryId, int points)
    : text(text), options(options), correctOption(correctOption),
    categoryId(categoryId), points(points) {
}

string Question::getText() const {
    return text;
}

vector<string> Question::getOptions() const {
    return options;
}

int Question::getCorrectOption() const {
    return correctOption;
}

int Question::getCategoryId() const {
    return categoryId;
}

int Question::getPoints() const {
    return points;
}

bool Question::isCorrect(int selectedOption) const {
    return selectedOption == correctOption;
}