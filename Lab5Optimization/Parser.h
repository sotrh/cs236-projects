#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

#include "DatalogProgram.h"
#include "Parameter.h"
#include "Scanner.h"
#include "Token.h"

class Parser
{
	Scanner scanner;
	DatalogProgram program;

	string ensure(TokenType);

	void parseSchemes();
	void parseScheme();
	void parseSchemeList();

	void parseFacts();
	void parseFact();
	void parseFactList();

	void parseRules();
	void parseRule();
	void parseRuleList();

	void parseQueries();
	void parseQuery();
	void parseQueryList();

	void parsePredicate(Predicate&);
	void parsePredicateList(Rule&);

	void parseParameter(Predicate&);
	void parseParameterList(Predicate&);

public:
	Parser(Scanner s) : scanner(s) {}
	~Parser() {}

	DatalogProgram parse();
};