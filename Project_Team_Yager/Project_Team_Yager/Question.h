#pragma once
#include <string>
#include <vector>
using namespace std;

struct Question {
    int id;
    string text;
    vector<string> options;
    int correctOption;
    string category;
    int weight;
};
