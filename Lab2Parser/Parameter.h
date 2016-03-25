#pragma once

#include <string>

using std::string;

class Parameter
{
	string value;

public:
	
	Parameter(string s) : value(s) {}
	~Parameter() {}
	
	string getValue() { return value; }
};