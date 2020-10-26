#pragma once

#include <stack>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Loader.h"

class Interpreter {
private:
	const std::string baseURL;
	std::string currentFile;
	std::unique_ptr<Loader> loader;

	std::vector<std::string> instructions;
	std::vector<std::string> stack;
	std::vector<std::string> callStack;

	std::map<std::string, std::string> variables;
	std::map<std::string, int> labelReferences;

	int currentPosition = 0;
public:
	Interpreter(std::string baseURL, std::string startFile);
	std::string startInterpreting();
	void setupPrequirements();
	std::string interpret(int position);
};