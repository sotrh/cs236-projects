#include "Rule.h"

string Rule::toString()
{
	stringstream ss;
	ss << predicate.toString();
	ss << ":-";

	for (unsigned i=0; i<predicateList.size(); i++)
	{
		if (i>0) ss << ",";
		ss << predicateList[i].toString();
	}

	return ss.str();
}