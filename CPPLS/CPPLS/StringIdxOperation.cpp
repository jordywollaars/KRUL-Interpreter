#include "StringIdxOperation.hpp"
#include "Utilities.hpp"

void StringIdxOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	if (stack.size() < 2)
		throw std::exception("Not enough values on the stack");
	
	if (!Utilities::isDigit(stack.back()))
		throw std::exception("Value could not be converted to an integer.");

	int index = std::stoi(stack.back());
	stack.pop_back();
	std::string str = stack.back();
	stack.pop_back();

	std::string character = str.substr(index, 1);
	stack.push_back(character);
}
