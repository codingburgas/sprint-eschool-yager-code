#include "question.h"


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