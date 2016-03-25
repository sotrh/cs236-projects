#include "Token.h"

std::ostream& operator<<(std::ostream& out, Token const &token)
{
	return out 
		<< std::string("(") 
		<< TokenTypeNames[token.type]
		<< std::string(",\"")
		<< token.value
		<< std::string("\",")
		<< std::string(std::to_string(token.lineNumber))
		<< std::string(")");
}