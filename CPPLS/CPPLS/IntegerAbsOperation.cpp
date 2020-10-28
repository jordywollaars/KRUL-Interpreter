#include "IntegerAbsOperation.hpp"
#include "Utilities.hpp"

void IntegerAbsOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	if (stack.empty())
		throw std::exception("Nothing on the stack.");

	if (!Utilities::isDigit(stack.back()))
		throw std::exception("Value could not be converted to an integer.");

	int val = std::stoi(stack.back());
	stack.pop_back();

	int newVal = std::abs(val);

	stack.push_back(std::to_string(newVal));
}
