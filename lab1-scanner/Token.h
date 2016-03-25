#pragma once

#include <string>
#include <sstream>

using std::stringstream;
using std::string;
using std::endl;

enum TokenType {
	COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, EOF_
};

const string TokenNames[] = {
	"COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN", "COLON", "COLON_DASH", "SCHEMES", "FACTS", "RULES", "QUERIES", "ID", "STRING", "EOF"
};

class Token
{
public:
	TokenType type;
	string value;
	int lineNumber;

	Token() : type(TokenType::EOF_), lineNumber(0) {}
	~Token() {}

	void recycle()
	{
		type = TokenType::EOF_;
		value = "";
		lineNumber = 0;
	}

	bool isEOF() { return type == TokenType::EOF_; }

	string toString()
	{
		stringstream ss;
		ss << "(" << TokenNames[type] << ",\"" << value << "\"," << lineNumber << ")";
		return ss.str();
	}
};