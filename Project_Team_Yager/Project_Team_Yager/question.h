#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>

using namespace std;

enum type {
    HISTORY,
    GEOGRAPHY,
    BIOLOGY,
    MATH,
    INFORMATICS,
    CATEGORY_COUNT
};

const string category_names[CATEGORY_COUNT] = {
    "History",
    "Geography",
    "Biology",
    "Math",
    "Informatics"
};

typedef struct {
    string text;
    string answer;
    string wrong1;
    string wrong2;
    string wrong3;
    enum type type;
} question;

vector<question> filterQuestionsByCategory(vector<question> allQuestions, int category);
vector<question> selectRandomSubset(vector<question> questionsList, size_t count, mt19937 rng);
vector<question> generate_exam();
bool ask(question question);