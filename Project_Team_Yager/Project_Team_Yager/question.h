#pragma once

#include <iostream>
#include <string>

using namespace std;

enum type {
    HISTORY,
    GEOGRAPHY,
    BIOLOGY,
    MATH,
    INFORMATICS
};

typedef struct question {
    string text;
    string answer;
    string wrong1;
    string wrong2;
    string wrong3;
    enum type type;
} question;
