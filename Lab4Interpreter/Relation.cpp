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
    for (uint i = 0; i < positions.size(); i++)
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
	for (uint i = 0; i < scheme.size(); i++)
	{
	    ss << scheme[i] << "=" << t[i];
	    if (i < scheme.size() - 1) ss << " ";
	}
	ss << endl;
    }
    return ss.str();
}

/*
 * Lab 4 Stuff
 */

Relation Relation::join(Relation& other, const string& name) const
{
    vector<string> newScheme;
    vector<pair<uint, uint>> joinColumns;

    newScheme = makeScheme(other.scheme, joinColumns);

    Relation r(name, newScheme);

    for (auto a : tuples)
    {
	for (auto b : other.tuples)
	{
	    if (canJoin(a, b, joinColumns))
	    {
		Tuple t = joinTuples(a, b, joinColumns);
		r.insert(t);
	    }
	}
    }

    return r;
}

vector<string> Relation::makeScheme(
	vector<string>& otherScheme,
	vector<pair<uint, uint>>&joinColumns) const
{
    vector<string> newScheme = scheme;
    for (uint i = 0; i < otherScheme.size(); i++)
    {
	auto it = std::find(newScheme.begin(), newScheme.end(), otherScheme[i]);
	if (it == newScheme.end()) newScheme.push_back(otherScheme[i]);
	else
	{
	    auto index = std::distance(newScheme.begin(), it);
	    joinColumns.push_back(pair<uint, uint>(index, i));
	}
    }
    return newScheme;
}

bool Relation::canJoin(Tuple& a, Tuple& b, vector<pair<uint, uint>>&joinColumns) const
{
    for (auto p : joinColumns)
    {
	if (a[p.first] != b[p.second]) return false;
    }
    return true;
}

Tuple Relation::joinTuples(Tuple& a, Tuple& b, vector<pair<uint, uint>>&joinColumns) const
{
    Tuple t = a;
    bool shouldAdd = false;
    for (uint i = 0; i < b.size(); i++)
    {
	shouldAdd = joinColumns.size() == 0;
	for (auto p : joinColumns)
	{
	    if (p.second != i)
	    {
		shouldAdd = true;
		break;
	    }
	}
	if (shouldAdd) t.insert(b[i]);
    }
    return t;
}

Relation Relation::unin(Relation& other) const
{
    Relation r(*this);
    for (auto t : other.tuples) r.insert(t);
    return r;
}

Relation Relation::diff(Relation& other) const
{
    Relation r(name, scheme);
    for (auto t : tuples)
    {
	if (other.tuples.find(t) == other.tuples.end()) r.insert(t);
    }
    return r;
}