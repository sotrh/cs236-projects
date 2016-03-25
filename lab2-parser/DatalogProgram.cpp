#include "DatalogProgram.h"

template<typename T>
void DatalogProgram::printList(stringstream& ss, string name, string punc, vector<T> list)
{
	ss << name << '(' << list.size() << "):" << endl;
	for (unsigned i=0; i<list.size(); i++)
	{
		ss << list[i].toString() << endl;
	}
}

string DatalogProgram::toString()
{
	stringstream ss;
	printList(ss, "Schemes", "", schemeList);
	printList(ss, "Facts", ".", factList);
	printList(ss, "Rules", "", ruleList);
	printList(ss, "Queries", "?", queryList);
	
	// Print the domain
	ss << "Domain(" << domain.size() << "):" << endl;
	unsigned size = domain.size();
	for (auto& s : domain)
	{
		ss << "  " << s;
		if (--size > 0) ss << endl;
	}

	return ss.str();
}