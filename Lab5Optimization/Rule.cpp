#include "Rule.h"

void Rule::add(Predicate p)
{
    predicateList.push_back(p);
}

string Rule::toString()
{
    stringstream ss;
    ss << predicate.toString() << " :- ";
    
    for (unsigned i=0; i<predicateList.size(); i++)
    {
        if (i>0) ss << ",";
        ss << predicateList[i].toString();
    }
    
    return ss.str();
}