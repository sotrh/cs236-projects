#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType
{
	COMMA, 
	PERIOD, 
	Q_MARK, 
	LEFT_PAREN, 
	RIGHT_PAREN,
	COLON,
	COLON_DASH,
	MULTIPLY,
	ADD,
	SCHEMES,
	FACTS,
	RULES,
	QUERIES,
	ID,
	STRING,
	COMMENT,
	WHITESPACE,
	UNDEFINED,
	EOF_
};

const std::string TokenTypeNames[] =
{
	std::string("COMMA"),
	std::string("PERIOD"),
	std::string("Q_MARK"),
	std::string("LEFT_PAREN"),
	std::string("RIGHT_PAREN"),
	std::string("COLON"),
	std::string("COLON_DASH"),
	std::string("MULTIPLY"),
	std::string("ADD"),
	std::string("SCHEMES"),
	std::string("FACTS"),
	std::string("RULES"),
	std::string("QUERIES"),
	std::string("ID"),
	std::string("STRING"),
	std::string("COMMENT"),
	std::string("WHITESPACE"),
	std::string("UNDEFINED"),
	std::string("EOF")
};

class Token
{
public:
	std::string value;
	TokenType type;
	unsigned int lineNumber;

	Token()
	{
		this->type = TokenType::EOF_;
	}

	Token(TokenType type, std::string value, unsigned int lineNumber)
	{
		this->value = value;
		this->type = type;
		this->lineNumber = lineNumber;
	}
	~Token() {}
};

std::ostream& operator <<(std::ostream& out, const Token& token);

#endif