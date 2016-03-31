/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tuple.h
 * Author: benjamin
 *
 * Created on February 26, 2016, 11:02 PM
 */

#ifndef TUPLE_H
#define TUPLE_H

#include <initializer_list>
#include <vector>
#include <string>

using std::initializer_list;
using std::vector;
using std::string;

class Tuple
{
    vector<string> values;
public:
    Tuple();
    Tuple(vector<string>& v) : values(v) {}
    Tuple(initializer_list<string> l) : values(l) {}
    Tuple(const Tuple& t) : values(t.values) {}
    virtual ~Tuple();
    
    string& operator[](const unsigned i) { return values[i]; }
    bool operator<(const Tuple t) const { return values < t.values; }
    
    void insert(string s) { values.push_back(s); }

    uint size() { return values.size(); }
};

#endif /* TUPLE_H */

