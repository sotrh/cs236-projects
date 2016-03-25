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
	for (Parameter p : s.getParameters())
	{
	    attributes.push_back(p.getValue());
	}
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

void Interpreter::evaluateQueries(DatalogProgram& program, ofstream& ofs, Database& d){
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

void Interpreter::interpret(DatalogProgram& program, ofstream& ofs)
{
    Database d;

    evaluateSchemes(program, ofs, d);
    evaluateFacts(program, ofs, d);
    evaluateQueries(program, ofs, d);
}

