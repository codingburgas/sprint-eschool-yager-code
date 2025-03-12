#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
using namespace std;

class Category {
private:
    int id;
    string name;
    string description;

public:
    Category();
    Category(int id, const string& name, const string& description);

    int getId() const;
    string getName() const;
    string getDescription() const;
};

#endif