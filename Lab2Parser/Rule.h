#pragma once

#include <sstream>
#include <string>
#include <vector>

using std::stringstream;
using std::string;
using std::vector;

#include "Predicate.h"
#include "Parameter.h"

class Rule
{
	Predicate predicate;
	vector<Predicate> predicateList;
public:
	Rule(Predicate p) : predicate(p) {}
	~Rule() {}
	
	void add(Predicate);
        
        string toString();
};