#include "FunctieRetOperation.hpp"

FunctieRetOperation::FunctieRetOperation(int& position) : currentPosition{position}
{
}

void FunctieRetOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	int loc = std::stoi(callStack.back());
	callStack.pop_back();

	this->currentPosition = loc - 1;
}
