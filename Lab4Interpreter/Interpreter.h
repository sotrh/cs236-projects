/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Interpreter.h
 * Author: benjamin
 *
 * Created on February 29, 2016, 10:23 PM
 */

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "DatalogProgram.h"
#include "Database.h"

using std::ofstream;
using std::vector;
using std::string;
using std::endl;
using std::map;

class Interpreter
{
    int indexOf(vector<string>&, string);
    void evaluateQueries(DatalogProgram& program, ofstream& ofs, Database& d);
    void displayQueryResults(ofstream& ofs, Predicate& q, Relation& select, Relation& project, Relation& rename);

    void performSelect(Predicate& q, Relation& select, vector<uint>& positions, vector<string>& renames);

    void evaluateFacts(DatalogProgram& program, ofstream& ofs, Database& d);
    void evaluateSchemes(DatalogProgram& program, ofstream& ofs, Database& d);
    
    void evaluateRules(DatalogProgram&, ofstream&, Database&);
    void evaluateRightSide(Rule&, Database&, vector<Relation>&);
    void extractAttributes(Predicate& s, vector<string>& attributes);
    void extractPositions(vector<string>&, Relation&, vector<uint>&);
    void extractScheme(DatalogProgram&, Rule&, vector<string>&);
    Relation joinRelations(vector<Relation>&);
public:
    Interpreter();
    Interpreter(const Interpreter& orig);
    virtual ~Interpreter();
    
    void interpret(DatalogProgram&, ofstream&);

};

#endif /* INTERPRETER_H */

