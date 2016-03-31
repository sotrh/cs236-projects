/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Interpreter.cpp
 * Author: benjamin
 * 
 * Created on February 29, 2016, 10:23 PM
 */

#include "Interpreter.h"

#include <iostream>
using std::cout;

Interpreter::Interpreter() { }

Interpreter::Interpreter(const Interpreter& orig) { }

Interpreter::~Interpreter() { }

void Interpreter::evaluateSchemes(DatalogProgram& program, ofstream& ofs, Database& d){
    ofs << "Scheme Evaluation" << endl << endl;
    for (Predicate s : program.getSchemes())
    {
	vector<string> attributes;
	extractAttributes(s, attributes);
	d.insert(Relation(s.name, attributes));
    }
}

void Interpreter::evaluateFacts(DatalogProgram& program, ofstream& ofs, Database& d){
    ofs << "Fact Evaluation" << endl << endl;
    for (Predicate f : program.getFacts())
    {
	vector<string> values;
	for (Parameter p : f.getParameters()) values.push_back(p.getValue());
	d[f.name].insert(Tuple(values));
    }
    ofs << d.toString() << endl;
}

int Interpreter::indexOf(vector<string>& vector, string value){
    for (uint i=0; i<vector.size(); i++)
    {
	if (vector.at(i) == value) return i;
    }
    return -1;
}

void Interpreter::performSelect(Predicate& q, Relation& select, vector<uint>& positions, vector<string>& renames){
    for (uint u = 0; u < q.getParameters().size(); u++)
    {
	Parameter p = q.getParameters()[u];
	switch (p.getValue()[0])
	{
	    case '\'':
		select = select.select(u, p.getValue());
		break;
	    default:
		int index = indexOf(renames, p.getValue());
		if (index >= 0) select = select.select(positions[index], u);
		else
		{
		    positions.push_back(u);
		    renames.push_back(p.getValue());
		}
		break;
	}
    }
}

void Interpreter::displayQueryResults(ofstream& ofs, Predicate& q, Relation& select, Relation& project, Relation& rename){
    ofs << q.toString() << "? ";
    if (select.size() > 0)
    {
	ofs << "Yes(" << select.size() << ")" << endl;
	ofs << "select" << endl;
	ofs << select.toString();
	ofs << "project" << endl;
	if (project.size() > 0)
	    ofs << project.toString();
	ofs << "rename" << endl;
	if (rename.size() > 0)
	    ofs << rename.toString();
	ofs << endl;
    }
    else ofs << "No" << endl << endl;
}

void Interpreter::evaluateQueries(DatalogProgram& program, ofstream& ofs, Database& d)
{
    ofs << "Query Evaluation" << endl << endl;
    for (Predicate q : program.getQueries())
    {
	// Perform select
	Relation select = d[q.name];
	vector<uint> positions;
	vector<string> renames;
	
	performSelect(q, select, positions, renames);
	Relation project = select.project(positions);
	Relation rename = project.rename(renames);
	displayQueryResults(ofs, q, select, project, rename);
    }
}

/*
 * Rule Evaluation Methods
 */

void Interpreter::evaluateRules(DatalogProgram& program, ofstream& ofs, Database& d)
{
    ofs << "Rule Evaluation" << endl << endl;
    uint oldSize = 0;
    uint passes = 0;
    do
    {
	oldSize = d.size();
	for (auto rule : program.getRules())
	{
	    // Get the relationsToJoin
	    vector<Relation> relationsToJoin;
	    evaluateRightSide(rule, d, relationsToJoin);

	    // Join said relations
	    Relation join = joinRelations(relationsToJoin);

	    // Clean up the result of the join
	    vector<string> attributes;
	    vector<uint> positions;
	    extractAttributes(rule.getHead(), attributes);
	    extractPositions(attributes, join, positions);
	    extractScheme(program, rule, attributes);
	    Relation project = join.project(positions);
	    Relation rename = project.rename(attributes);

	    // Union the intermediate relation with database
	    ofs << rule.toString() << endl;
	    ofs << rename.diff(d[rule.getHead().name]).toString();
	    d[rule.getHead().name] = d[rule.getHead().name].unin(rename);
	}
	passes++;
    } while (oldSize < d.size());
    
    ofs << endl << "Converged after " << passes << " passes through the Rules." << endl << endl;
    ofs << d.toString() << endl;
}

void Interpreter::evaluateRightSide(Rule& rule, Database& d, vector<Relation>& rtj)
{
    for (auto p : rule.getPredicateList())
    {
	Relation select = d[p.name];
	vector<uint> positions;
	vector<string> renames;
	
	performSelect(p, select, positions, renames);
	Relation project = select.project(positions);
	Relation rename = project.rename(renames);
	rtj.push_back(rename);
    }
}

Relation Interpreter::joinRelations(vector<Relation>& rtj)
{
    Relation r = rtj[0];
    for (uint u=1; u<rtj.size(); u++) r = r.join(rtj[u], r.getName());
    return r;
}

void Interpreter::extractAttributes(Predicate& predicate, vector<string>& attributes){
    for (Parameter p : predicate.getParameters())
    {
	attributes.push_back(p.getValue());
    }
}

void Interpreter::extractPositions(vector<string>& attributes, Relation& r, vector<uint>& positions)
{
    for (auto a : attributes)
    {
	for (uint u=0; u<r.getAttributes().size(); u++)
	{
	    if (a == r.getAttributes()[u]) {
		positions.push_back(u);
		break;
	    }
	}
    }
}

void Interpreter::extractScheme(DatalogProgram& d, Rule& r, vector<string>& scheme)
{
    scheme.clear();
    for (auto s : d.getSchemes())
    {
	if (s.name == r.getHead().name)
	{
	    extractAttributes(s, scheme);
	    break;
	}
    }
}

void Interpreter::interpret(DatalogProgram& program, ofstream& ofs)
{
    Database d;

    evaluateSchemes(program, ofs, d);
    evaluateFacts(program, ofs, d);
    evaluateRules(program, ofs, d);
    evaluateQueries(program, ofs, d);
}

