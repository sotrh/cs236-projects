#include <iostream>
#include <fstream>
#include <vector>

#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "DatalogProgram.h"

using std::ifstream;
using std::ofstream;
using std::vector;
using std::cout;
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
			Parser parser(scanner);
			DatalogProgram program = parser.parse();

			ofs << "Success!" << endl;
			ofs << program.toString();
		}
		catch(Token t)
		{
			ofs << "Failure!" << endl;
			ofs << "  " << t.toString() << endl;
		}

		// Close input and output files
		ifs.close();
		ofs.close();
	}

	return 0;
}