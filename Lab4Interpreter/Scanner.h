#pragma once

#include <map>
#include <string>
#include <istream>
#include <cctype>

#include "Token.h"

using std::map;
using std::string;
using std::istream;

const map<string, TokenType> keywords =
{
	{"Schemes", TokenType::SCHEMES},
	{"Facts", TokenType::FACTS},
	{"Rules", TokenType::RULES},
	{"Queries", TokenType::QUERIES}
};

class Scanner
{
	istream* stream;
	int lineNumber;
	Token currentToken;

	void skipWS();
	void skipComments();

	void scanToken();
	void scanString();
	void scanId();

	void checkIfKeyword();

public:
	Scanner(istream* is) : stream(is), lineNumber(1) {}
	~Scanner() {}
	
	Token next();
	Token peek();
};