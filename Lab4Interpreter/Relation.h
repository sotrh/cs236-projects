/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Relation.h
 * Author: benjamin
 *
 * Created on February 26, 2016, 11:05 PM
 */

#ifndef RELATION_H
#define RELATION_H


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

#include "Tuple.h"

using std::stringstream;
using std::string;
using std::vector;
using std::endl;
using std::set;
using std::cout;
using std::pair;

class Relation
{
    string name;
    set<Tuple> tuples;
    vector<string> scheme;
    
    void makeScheme(vector<string>&,vector<string>&,vector<pair<uint,uint>>&) const;
    bool canJoin(Tuple&,Tuple&,vector<pair<uint,uint>>&) const;
    Tuple joinTuples(Tuple&,Tuple&,vector<pair<uint,uint>>&) const;
    
public:
    Relation() {}
    Relation(const Relation& r) : name(r.name), tuples(r.tuples), scheme(r.scheme) {}
    Relation(string name, vector<string> scheme) : name(name), scheme(scheme) {}
    virtual ~Relation() {}
    
    Relation select(unsigned, string) const;
    Relation select(unsigned, unsigned) const;
    Relation project(vector<unsigned>&) const;
    Relation rename(vector<string>&) const;
    
    Relation join(Relation&,const string&) const;
    Relation unin(Relation&) const;
    Relation diff(Relation&) const;
    
    void insert(Tuple t) { tuples.insert(t); }
    
    bool operator<(const Relation& r) const { return tuples < r.tuples; }
    
    vector<string> getAttributes() const { return scheme; }
    string getName() const { return name; }
    string toString() const;
    
    uint size() const { return tuples.size(); }
};

#endif /* RELATION_H */

