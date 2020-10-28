#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <stack>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Loader.hpp"
#include "IInstruction.hpp"

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
	std::unique_ptr<IInstruction> getOperation(std::string op);
};

#endif //INTERPRETER_HPP