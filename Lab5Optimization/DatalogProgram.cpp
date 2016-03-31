#include "DatalogProgram.h"


template<typename T>
void DatalogProgram::printList(stringstream& ss, string name,vector<T> list)
{
	ss << name << '(' << list.size() << "):" << endl;
	for (T t : list)
        {
            ss << "  " << t.toString() << endl;
        }
}

string DatalogProgram::toString()
{
	stringstream ss;
	printList(ss, "Schemes", schemeList);
	printList(ss, "Facts", factList);
	printList(ss, "Rules", ruleList);
	printList(ss, "Queries", queryList);
	
	// Print the domain
	ss << "Domain(" << domain.size() << "):" << endl;
	for (auto& s : domain)
	{
		ss << "  " << s << endl;
	}

	return ss.str();
}