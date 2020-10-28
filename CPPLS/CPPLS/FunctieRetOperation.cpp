#include "FunctieRetOperation.hpp"
#include "Utilities.hpp"

FunctieRetOperation::FunctieRetOperation(int& position) : currentPosition{position}
{
}

void FunctieRetOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	if (callStack.empty())
		throw std::exception("Nothing found on the callstack.");

	std::string locAsString = callStack.back();
	callStack.pop_back();

	if (!Utilities::isDigit(locAsString))
		throw std::exception("Could not convert value on the callstack to integer.");

	int locAsInt = std::stoi(locAsString);

	this->currentPosition = locAsInt - 1;
}
