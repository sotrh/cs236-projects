#include "Scanner.h"

#include <iostream>
using std::cout;
using std::endl;

void Scanner::skipWS()
{
    while (isspace(stream->peek()))
    {
	if (stream->peek() == '\n') lineNumber++;
	stream->get();
    }
}

void Scanner::skipComments()
{
    if (stream->peek() != '#')
	return;

    stream->get();
    while (stream->peek() != '\n')
	stream->get();
}

void Scanner::scanToken()
{
    currentToken.recycle();
    while (stream->peek() != EOF)
    {
	switch (stream->peek())
	{
	    case ' ':
	    case '\t':
	    case '\r':
	    case '\n':
		skipWS();
		continue;
	    case '#':
		skipComments();
		continue;
	    case ':':
		currentToken.value = (char) stream->get();
		currentToken.type = TokenType::COLON;
		if (stream->peek() == '-')
		{
		    currentToken.value += (char) stream->get();
		    currentToken.type = TokenType::COLON_DASH;
		}
		break;
	    case ',':
		currentToken.type = TokenType::COMMA;
		currentToken.value = (char) stream->get();
		break;
	    case '.':
		currentToken.type = TokenType::PERIOD;
		currentToken.value = (char) stream->get();
		break;
	    case '?':
		currentToken.type = TokenType::Q_MARK;
		currentToken.value = (char) stream->get();
		break;
	    case '(':
		currentToken.type = TokenType::LEFT_PAREN;
		currentToken.value = (char) stream->get();
		break;
	    case ')':
		currentToken.type = TokenType::RIGHT_PAREN;
		currentToken.value = (char) stream->get();
		break;
	    case '\'':
		scanString();
		break;
	    default:
		scanId();
		break;
	}
	break;
    }
    currentToken.lineNumber = lineNumber;
}

void Scanner::scanString()
{
    currentToken.type = TokenType::STRING;
    currentToken.value = (char) stream->get();
    while (stream->peek() != '\'')
    {
	if (stream->peek() == EOF || stream->peek() == '\n') throw lineNumber;
	currentToken.value += (char) stream->get();
    }
    currentToken.value += (char) stream->get();
}

void Scanner::scanId()
{
    currentToken.type = TokenType::ID;
    if (!isalpha(stream->peek())) throw lineNumber;
    currentToken.value = (char) stream->get();
    while (isalnum(stream->peek()))
	currentToken.value += (char) stream->get();

    checkIfKeyword();
}

void Scanner::checkIfKeyword()
{
    auto search = keywords.find(currentToken.value);
    if (search != keywords.end()) currentToken.type = search->second;
}

Token Scanner::next()
{
    if (currentToken.isEOF())
    {
	scanToken();
	return currentToken;
    }
    
    Token temp = currentToken;
    currentToken.recycle();
    return temp;
}

Token Scanner::peek()
{
    if (currentToken.isEOF())
	scanToken();
    return currentToken;
}