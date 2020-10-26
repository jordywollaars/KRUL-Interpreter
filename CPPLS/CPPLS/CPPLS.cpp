#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include "curl/curl.h"
#include "Loader.h"
#include "Interpreter.h"

#define FIRST "start.txt"
#define SECOND "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.txt"
#define THIRD "4812-9-6727.txt"
#define FOURTH "AasHgsho.txt"
#define FIFTH "Bososen-hosgen-in-warme-losden-aos-de-bososenboom.txt"
#define SIXTH "we-zijn-er-bijna.txt"
#define SEVENTH "ninaf-zvabe-fjn-pcc1.txt"

int main(int argc, char* argv[])
{
	const std::string base = "https://www.swiftcoder.nl/cpp1/";
	
	Interpreter* interpreter = new Interpreter(base, FIRST);
	
	std::string output;
	output = interpreter->startInterpreting();

	delete interpreter;

	system("cls");
	std::cout << "Message found: " << std::endl << output << std::endl;

	return 0;
}
