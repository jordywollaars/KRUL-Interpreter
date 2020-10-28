#include "StringSlcOperation.hpp"
#include "Utilities.hpp"

void StringSlcOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	if (stack.size() < 3)
		throw std::exception("Not enough values on the stack.");
	
	if (!Utilities::isDigit(stack.back()))
		throw std::exception("Value could not be converted to an integer.");

	int to = std::stoi(stack.back());
	stack.pop_back();

	if (!Utilities::isDigit(stack.back()))
		throw std::exception("Value could not be converted to an integer.");

	int from = std::stoi(stack.back());
	stack.pop_back();

	std::string val = stack.back();
	stack.pop_back();

	std::string newVal = val.substr(from, (to - from));

	stack.push_back(newVal);
}
