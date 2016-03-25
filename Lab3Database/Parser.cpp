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
    ensure(TokenType::EOF_);
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
    Predicate scheme;
    parsePredicate(scheme);
    program.addScheme(scheme);
}

void Parser::parseSchemeList()
{
    switch (scanner.peek().type)
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
    Predicate fact;
    parsePredicate(fact);
    ensure(TokenType::PERIOD);
    program.addFact(fact);
}

void Parser::parseFactList()
{
    switch (scanner.peek().type)
    {
	case TokenType::ID:
	    parseFact();
	    parseFactList();
	    break;
	default: break;
    }
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
    // Parse the main predicate
    Predicate p;
    parsePredicate(p);
    ensure(TokenType::COLON_DASH);

    // Parse the predicate list
    Rule rule(p);
    p.recycle();
    parsePredicate(p);
    rule.add(p);
    parsePredicateList(rule);
    ensure(TokenType::PERIOD);

    program.addRule(rule);
}

void Parser::parseRuleList()
{
    switch (scanner.peek().type)
    {
	case TokenType::ID:
	    parseRule();
	    parseRuleList();
	    break;
	default: break;
    }
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
    Predicate query;
    parsePredicate(query);
    ensure(TokenType::Q_MARK);
    program.addQuery(query);
}

void Parser::parseQueryList()
{
    switch (scanner.peek().type)
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

void Parser::parsePredicate(Predicate& out)
{
    out.name = ensure(TokenType::ID);
    ensure(TokenType::LEFT_PAREN);
    parseParameter(out);
    parseParameterList(out);
    ensure(TokenType::RIGHT_PAREN);
}

void Parser::parsePredicateList(Rule& out)
{
    Predicate p;
    switch (scanner.peek().type)
    {
	case TokenType::COMMA:
	    ensure(TokenType::COMMA);
	    parsePredicate(p);
	    out.add(p);
	    parsePredicateList(out);
	    break;
	default: break;
    }
}

// *=======================
// * Parameters
// *=======================

void Parser::parseParameter(Predicate& out)
{
    switch (scanner.peek().type)
    {
	case TokenType::STRING:
	    program.addDomain(scanner.peek().value);
	case TokenType::ID:
	    out.add(Parameter(scanner.next().value));
	    break;
	default:
	    throw scanner.next();
    }
}

void Parser::parseParameterList(Predicate& out)
{
    switch (scanner.peek().type)
    {
	case TokenType::COMMA:
	    ensure(TokenType::COMMA);
	    parseParameter(out);
	    parseParameterList(out);
	    break;
	default: break;
    }
}