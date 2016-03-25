#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <set>

using std::stringstream;
using std::string;
using std::vector;
using std::endl;
using std::set;

#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"
class DatalogProgram
{
	vector<Predicate> schemeList;
	vector<Predicate> factList;
	vector<Rule> ruleList;
	vector<Predicate> queryList;
	set<string> domain;

	template<typename T> void printList(stringstream&, string, vector<T>);

public:
	DatalogProgram() {}
	~DatalogProgram() {}

	void addScheme(Predicate s) { schemeList.push_back(s); }
	void addFact(Predicate f) { factList.push_back(f); }
	void addRule(Rule r) { ruleList.push_back(r); }
	void addQuery(Predicate q) { queryList.push_back(q); }
	void addDomain(string s) { domain.insert(s); }
	
	vector<Predicate> getSchemes() const { return schemeList; }
	vector<Predicate> getFacts() const { return factList; }
	vector<Rule>      getRules() const { return ruleList; }
	vector<Predicate> getQueries() const { return queryList; }
	
	string toString();
};