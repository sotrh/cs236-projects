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

#include "Tuple.h"

using std::stringstream;
using std::string;
using std::vector;
using std::endl;
using std::set;
using std::cout;

class Relation
{
    string name;
    set<Tuple> tuples;
    vector<string> scheme;
    
public:
    Relation() {}
    Relation(const Relation& r) : name(r.name), tuples(r.tuples), scheme(r.scheme) {}
    Relation(string name, vector<string> scheme) : name(name), scheme(scheme) {}
    virtual ~Relation() {}
    
    Relation select(unsigned, string) const;
    Relation select(unsigned, unsigned) const;
    Relation project(vector<unsigned>&) const;
    Relation rename(vector<string>&) const;
    
    void insert(Tuple t) { tuples.insert(t); }
    
    bool operator<(const Relation r) const { return tuples < r.tuples; }
    
    string getName() const { return name; }
    string toString() const;
    
    uint size() const { return tuples.size(); }
};

#endif /* RELATION_H */

