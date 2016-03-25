#ifndef BETTERLEXER_H
#define BETTERLEXER_H

#include <iostream>

#include "Scanner.h"
#include "Token.h"

class BetterLexer
{
private:
	Scanner* scanner;
	int currentLine;

	bool atEOF() { return !scanner->peek() || scanner->peek() == EOF; }

	void processWhitespace(Token& token);
	void processAlphaNumeric(Token& token);
	void processOther(Token& token);

	void processKeyword(Token& token);

	void processComment(Token& token);
	void processCommentBlock(Token& token);

	void processString(Token& token);

	void processColon(Token& token);

	void processSymbol(Token& token);

public:
	BetterLexer(Scanner* scanner);
	~BetterLexer() {}

	Token next();
};

#endif