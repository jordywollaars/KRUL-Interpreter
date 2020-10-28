#include <iostream>
#include <stack>
#include <memory>
#include <string>
#include <sstream>
#include "curl/curl.h"
#include "Loader.hpp"
#include "Interpreter.hpp"

#include <crtdbg.h>
#include "Utilities.hpp"

#define FIRST "start.txt"
#define SECOND "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.txt"
#define THIRD "4812-9-6727.txt"
#define FOURTH "AasHgsho.txt"
#define FIFTH "Bososen-hosgen-in-warme-losden-aos-de-bososenboom.txt"
#define SIXTH "we-zijn-er-bijna.txt"
#define SEVENTH "ninaf-zvabe-fjn-pcc1.txt"

void start()
{
	const std::string base = "https://www.swiftcoder.nl/cpp1/";

	std::unique_ptr<Interpreter> interpreter = std::make_unique<Interpreter>(base, FIRST);

	std::string output = interpreter->startInterpreting();

	std::cout << SECTIONDIVIDER << std::endl;
	std::cout << output << std::endl;
}

int main(int argc, char* argv[])
{
	start();
	_CrtDumpMemoryLeaks();

	return 0;
}
