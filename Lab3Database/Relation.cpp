/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Relation.cpp
 * Author: benjamin
 * 
 * Created on February 26, 2016, 11:05 PM
 */

#include "Relation.h"
#include "Predicate.h"

Relation Relation::select(unsigned position, string value) const
{
    Relation r(name, scheme);
    for (Tuple t : tuples)
    {
	if (t[position] == value) r.insert(t);
    }
    return r;
}

Relation Relation::select(unsigned pos, unsigned pos1) const
{
    Relation r(name, scheme);
    for (Tuple t : tuples)
    {
	if (t[pos] == t[pos1]) r.insert(t);
    }
    return r;
}

Relation Relation::project(vector<unsigned>& positions) const
{
    if (positions.size() == 0) return Relation(name, scheme);
    
    vector<string> scheme;
    for (uint i=0; i<positions.size(); i++) 
    {
	scheme.push_back(this->scheme[positions[i]]);
    }
    
    Relation r(name, scheme);
    for (Tuple t : tuples)
    {
	Tuple temp;
	for (unsigned u : positions) 
	{
	    temp.insert(t[u]);
	}
	r.insert(temp);
    }
    
    return r;
}

Relation Relation::rename(vector<string>& names) const
{
    Relation r(name, names);
    r.tuples = tuples;
    return r;
}

string Relation::toString() const
{
    stringstream ss;
    for (Tuple t : tuples)
    {
	ss << "  ";
	for (uint i=0; i<scheme.size(); i++)
	{
	    ss << scheme[i] << "=" << t[i];
	    if (i<scheme.size() - 1) ss << " ";
	}
	ss << endl;
    }
    return ss.str();
}