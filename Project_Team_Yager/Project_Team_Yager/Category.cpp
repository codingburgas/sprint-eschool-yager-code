#include "Category.h"
using namespace std;

Category::Category() : id(0) {}

Category::Category(int id, const string& name, const string& description)
    : id(id), name(name), description(description) {
}

int Category::getId() const {
    return id;
}

string Category::getName() const {
    return name;
}

string Category::getDescription() const {
    return description;
}