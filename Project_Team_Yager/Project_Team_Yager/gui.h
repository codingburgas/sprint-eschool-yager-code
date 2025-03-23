#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

#include "question.h"
#include "exam.h"


using namespace std;

void menu();
enum type select_category();
void print_stats(
    unsigned correct_answers,
    unsigned total_questions,
    long exam_duration_seconds,
    vector<unsigned> per_category_correct);