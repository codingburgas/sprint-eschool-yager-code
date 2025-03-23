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

vector<question> generate_exam() {
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