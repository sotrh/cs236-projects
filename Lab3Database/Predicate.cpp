#include "Predicate.h"

Parameter& Predicate::operator[](int i)
{
    return parameterList[i];
}

string Predicate::getName()
{
    return name;
}

int Predicate::size()
{
    return parameterList.size();
}

void Predicate::add(Parameter p)
{
    parameterList.push_back(p);
}

void Predicate::recycle()
{
    name.clear();
    parameterList.clear();
}

string Predicate::toString()
{
    stringstream ss;
    ss << name << "(";
    for (unsigned i = 0; i < parameterList.size(); i++)
    {
	if (i > 0) ss << ",";
	ss << parameterList[i].getValue();
    }
    ss << ")";

    return ss.str();
}