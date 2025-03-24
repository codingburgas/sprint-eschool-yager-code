#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

#include "user.h"

using namespace std;

vector<user> loadUsersFromFile(string filename) {

    vector<user> loadedUsers;

    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Could not open file " << filename << " for reading." << endl;
        return loadedUsers;
    }

    string line;
    while (getline(infile, line)) {
        // Skip any blank lines between users.
        if (line.empty())
            continue;

        user currentUser;
        // First line: user's name.
        currentUser.name = line;

        // Second line: total_questions, correct_answers, exam_duration_seconds.
        if (!getline(infile, line))
            break;
        istringstream iss(line);
        iss >> currentUser.total_questions >> currentUser.correct_answers >> currentUser.exam_duration_seconds;

        // Third line: per_category_correct values (space separated).
        if (!getline(infile, line))
            break;
        istringstream iss2(line);
        unsigned val;
        while (iss2 >> val) {
            currentUser.per_category_correct.push_back(val);
        }

        // Read the blank line that separates users (if present)
        getline(infile, line);

        loadedUsers.push_back(currentUser);
    }

    infile.close();
    return loadedUsers;
}
﻿