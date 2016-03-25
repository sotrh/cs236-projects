/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataBase.cpp
 * Author: benjamin
 * 
 * Created on February 27, 2016, 11:27 AM
 */

#include "Database.h"

Database::Database() { }

Database::Database(const Database& orig) : relations(orig.relations) { }

Database::~Database() { }

void Database::insert(Relation r)
{
    relations[r.getName()] = r;
}

string Database::toString()
{
    stringstream ss;
    uint u=0;
    for (auto& kv : relations) 
    {
	if (u++>0) ss << endl;
	ss << kv.second.getName() << endl;
	ss << kv.second.toString();
    }
    return ss.str();
}

