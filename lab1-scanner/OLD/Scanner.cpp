#include "Scanner.h"

Scanner::Scanner(char* filename)
{
	file.open(filename);
}

const char Scanner::get()
{
	return file.get();
}

const char Scanner::peek()
{
	return file.peek();
}