#pragma once

#include <string>
#include <vector>

using namespace std;

typedef struct {
    string name;
    unsigned correct_answers;
    unsigned total_questions;
    long exam_duration_seconds;
    vector<unsigned> per_category_correct;
} user;

vector<user> loadUsersFromFile(string filename);