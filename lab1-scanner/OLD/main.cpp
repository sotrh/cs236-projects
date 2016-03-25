#include <iostream>

#include "util.h"
#include "Scanner.h"
#include "BetterLexer.h"

void performLexing(BetterLexer& lexer) {
	Token token = lexer.next();
	int totalTokens = 1;
	
	while (token.type != TokenType::EOF_)
	{
		std::cout << token << std::endl;
		token = lexer.next();
		totalTokens++;
	}

	std::cout << token << std::endl;
	std::cout << "Total Tokens = " << totalTokens << std::endl;
}

int main(int argc, char *argv[])
{
	if (argc > 1) {
		// std::string contents = readFile(argv[1]);
		// if (contents.size() > 0)
		// {
		// 	Lexer lexer(contents);
		// 	Token test = lexer.next();
		// 	while (test.getType() != TokenType::EOF_)
		// 	{
		// 		std::cout << test << std::endl;
		// 		test = lexer.next();
		// 	}
		// 	std::cout << test << std::endl;
		// }

		// Create the scanner
		Scanner scanner(argv[1]);

		// Create the lexer with the scanner
		BetterLexer lexer(&scanner);

		// Perform the lexing
		performLexing(lexer);
	}
	return 0;
}