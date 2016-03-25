/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataBase.h
 * Author: benjamin
 *
 * Created on February 27, 2016, 11:27 AM
 */

#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <string>
#include <sstream>

#include "Relation.h"

using std::map;
using std::endl;
using std::pair;
using std::string;
using std::stringstream;

class Database
{
    map<string,Relation> relations;
public:
    Database();
    Database(const Database& orig);
    virtual ~Database();
    
    Relation& operator[](const string key) { return relations[key]; }
    bool operator<(const Database& d) const { return relations < d.relations; }
    
    void insert(Relation);
    
    uint size() const;
    string toString() const;
};

#endif /* DATABASE_H */

