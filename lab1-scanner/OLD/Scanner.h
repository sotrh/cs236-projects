#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <fstream>

class Scanner
{
private:
	std::ifstream file;

public:
	Scanner() {}
	Scanner(char* filename);
	~Scanner() {}
	
	const char get();
	const char peek();
};

#endif