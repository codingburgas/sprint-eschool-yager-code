#include "User.h"
#include <functional>
using namespace std;

User::User() : isTeacher(false) {}

User::User(const string& username, const string& password, bool isTeacher)
    : username(username), isTeacher(isTeacher) {
    passwordHash = hashPassword(password);
}

string User::getUsername() const {
    return username;
}

bool User::validatePassword(const string& password) const {
    return hashPassword(password) == passwordHash;
}

bool User::getIsTeacher() const {
    return isTeacher;
}

void User::addTestResult(int score) {
    testResults.push_back(score);
}

vector<int> User::getTestResults() const {
    return testResults;
}

string User::hashPassword(const string& password) const {
    //Hashes the given password
    hash<string> hasher;
    size_t hash = hasher(password);
    return to_string(hash);
}