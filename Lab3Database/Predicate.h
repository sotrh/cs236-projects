#pragma once

#include <sstream>
#include <string>
#include <vector>

using std::stringstream;
using std::string;
using std::vector;
using std::endl;

#include "Parameter.h"

class Predicate
{
    vector<Parameter> parameterList;

public:
    string name;

    Predicate() { }

    Predicate(string s) : name(s) { }

    ~Predicate() { }

    Parameter& operator[](int);
    string getName();
    int size();

    void add(Parameter);
    void recycle();
    
    vector<Parameter> getParameters() const { return parameterList; }

    string toString();
};