#include "Parser.h"

#include <iostream>
using std::cout;
using std::endl;

DatalogProgram Parser::parse()
{
	parseSchemes();
	parseFacts();
	parseRules();
	parseQueries();
	return program;
}

string Parser::ensure(TokenType t)
{
	if (scanner.peek().type != t) throw scanner.peek();
	return scanner.next().value;
}

// *=======================
// * Schemes
// *=======================

void Parser::parseSchemes()
{
	ensure(TokenType::SCHEMES);
	ensure(TokenType::COLON);
	parseScheme();
	parseSchemeList();
}
void Parser::parseScheme()
{
	program.addScheme(parsePredicate());
}
void Parser::parseSchemeList()
{
	switch(scanner.peek().type)
	{
		case TokenType::ID:
			parseScheme();
			parseSchemeList();
		default: break;
	}
}

// *=======================
// * Facts
// *=======================

void Parser::parseFacts()
{
	ensure(TokenType::FACTS);
	ensure(TokenType::COLON);
	parseFactList();
}
void Parser::parseFact()
{
}
void Parser::parseFactList()
{
}

// *=======================
// * Rules
// *=======================

void Parser::parseRules()
{
	ensure(TokenType::RULES);
	ensure(TokenType::COLON);
	parseRuleList();
}
void Parser::parseRule()
{
}
void Parser::parseRuleList()
{
}

// *=======================
// * Queries
// *=======================

void Parser::parseQueries()
{
	ensure(TokenType::QUERIES);
	ensure(TokenType::COLON);
	parseQuery();
	parseQueryList();
}
void Parser::parseQuery()
{
	program.addQuery(parsePredicate());
	ensure(TokenType::Q_MARK);
}
void Parser::parseQueryList()
{
	switch(scanner.peek().type)
	{
		case TokenType::ID:
			parseQuery();
			parseQueryList();
			break;
		default: break;
	}
}

// *=======================
// * Predicates
// *=======================

Predicate Parser::parsePredicate()
{
	Predicate p(ensure(TokenType::ID));
	ensure(TokenType::LEFT_PAREN);
	parseParameter(p);
	parseParameterList(p);
	ensure(TokenType::RIGHT_PAREN);
	return p;
}
void Parser::parsePredicateList()
{
}

// *=======================
// * Parameters
// *=======================

void Parser::parseParameter(Predicate& p)
{
	switch(scanner.peek().type)
	{
		case TokenType::STRING:
			program.addDomain(scanner.peek().value);
		case TokenType::ID:
			p.add(Parameter(scanner.next().value));
			break;
		default:
			throw scanner.next();
	}
}
void Parser::parseParameterList(Predicate& p)
{
	switch(scanner.peek().type)
	{
		case TokenType::COMMA:
			ensure(TokenType::COMMA);
			parseParameter(p);
			parseParameterList(p);
			break;
		default: break;
	}
}