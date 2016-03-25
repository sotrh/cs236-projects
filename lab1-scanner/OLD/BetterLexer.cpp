#include "BetterLexer.h"

BetterLexer::BetterLexer(Scanner* scanner) 
{
	this->scanner = scanner;
	this->currentLine = 1;
}

Token BetterLexer::next() 
{
	Token token;

	// Scan through whitespace looking for newlines
	processWhitespace(token);
	token.lineNumber = currentLine;

	// Escape if at the end
	if (atEOF()) return token;

	// If we find any characters try to process them
	if (std::isalpha(scanner->peek())) processAlphaNumeric(token);
	else processOther(token);

	return token;
}

// Basic processing
void BetterLexer::processWhitespace(Token& token)
{
	while (std::isspace(scanner->peek()))
	{
		if (scanner->get() == '\n') currentLine++;
	}
}

void BetterLexer::processAlphaNumeric(Token& token)
{
	token.type = TokenType::ID;

	while (!atEOF() && std::isalnum(scanner->peek()))
	{
		token.value += scanner->get();
	}

	processKeyword(token);
}

void BetterLexer::processOther(Token& token)
{
	char c = scanner->peek();
	switch (c)
	{
		case '#': processComment(token); break;
		case '\'': processString(token); break;
		case ':': processColon(token); break;
		default: processSymbol(token); break;
	}
}

// Advanced processing

// Keyword processing
void BetterLexer::processKeyword(Token& token)
{
	if (token.value.compare("Schemes") == 0)
		token.type = TokenType::SCHEMES;
	else if (token.value.compare("Facts") == 0)
		token.type = TokenType::FACTS;
	else if (token.value.compare("Rules") == 0)
		token.type = TokenType::RULES;
	else if (token.value.compare("Queries") == 0)
		token.type = TokenType::QUERIES;
}

// Comment processing
void BetterLexer::processComment(Token& token)
{
	token.value += scanner->get();
	token.type = TokenType::COMMENT;

	if (scanner->peek() == '|') processCommentBlock(token);
	else
	{
		while (!atEOF() && scanner->peek() != '\n') token.value += scanner->get();
	}
}

void BetterLexer::processCommentBlock(Token& token)
{
	token.value += scanner->get();
	bool foundBar = false;

	while (!atEOF())
	{
		if (scanner->peek() == '|') foundBar = true;
		else if (scanner->peek() == '#' && foundBar)
		{
			token.value += scanner->get();
			break;
		}
		else if (scanner->peek() == '\n') currentLine++;
		else foundBar = false;

		token.value += scanner->get();
	}

	if (!foundBar) token.type = TokenType::UNDEFINED;
}

// String processing
void BetterLexer::processString(Token& token)
{
	token.value = scanner->get();
	bool foundQuote = false;

	while (!atEOF())
	{
		if (scanner->peek() == '\n') currentLine++;
		if (scanner->peek() == '\'')
		{
			token.value += scanner->get();
			if (scanner->peek() != '\'')
			{
				foundQuote = true;
				break;
			}
		}

		token.value += scanner->get();
	}

	token.type = foundQuote ? TokenType::STRING : TokenType::UNDEFINED;
}

// Colon processing
void BetterLexer::processColon(Token& token)
{
	token.value = scanner->get();
	if (scanner->peek() == '-')
	{
		token.value += scanner->get();
		token.type = TokenType::COLON_DASH;
	}
	else token.type = TokenType::COLON;
}

// Symbol processing
void BetterLexer::processSymbol(Token& token)
{
	char c = scanner->peek();
	switch (c)
	{
		case '+': token.type = TokenType::ADD; break;
		case ',': token.type = TokenType::COMMA; break;
		case '.': token.type = TokenType::PERIOD; break;
		case '?': token.type = TokenType::Q_MARK; break;
		case '*': token.type = TokenType::MULTIPLY; break;
		case '(': token.type = TokenType::LEFT_PAREN; break;
		case ')': token.type = TokenType::RIGHT_PAREN; break;
		default: token.type = TokenType::UNDEFINED; break;
	}

	token.value = scanner->get();
}