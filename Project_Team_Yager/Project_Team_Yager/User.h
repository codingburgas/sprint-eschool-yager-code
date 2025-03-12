#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
using namespace std;

class User {
private:
    string username;
    string passwordHash;
    bool isTeacher;
    vector<int> testResults;

public:
    User();
    User(const string& username, const string& password, bool isTeacher = false);

    string getUsername() const;
    bool validatePassword(const string& password) const;
    bool getIsTeacher() const;
    void addTestResult(int score);
    vector<int> getTestResults() const;

    string hashPassword(const string& password) const;
};

#endif