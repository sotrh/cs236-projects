#include <iostream>
#include <fstream>
#include <vector>

#include "Token.h"
#include "Scanner.h"

using std::ifstream;
using std::ofstream;
using std::vector;
using std::endl;

int main(int argc, char* argv[])
{
	if (argc > 2)
	{
		// Open input and output files
		ifstream ifs(argv[1]);
		ofstream ofs(argv[2]);

		try
		{
			Scanner scanner(&ifs);

			Token token = scanner.next();
			int numTokens = 1;
			while (!token.isEOF())
			{
				ofs << token.toString() << endl;
				token = scanner.next();
				numTokens++;
			}
			ofs << token.toString() << endl;
			ofs << "Total Tokens = " << numTokens << endl;
		}
		catch(int lineNumber)
		{
			ofs << "Input Error on line " << lineNumber << endl;
		}

		// Close input and output files
		ifs.close();
		ofs.close();
	}

	return 0;
}