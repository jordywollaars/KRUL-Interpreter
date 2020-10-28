#include "StringCatOperation.hpp"

void StringCatOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	if (stack.size() < 2)
		throw std::exception("Not enough values on the stack");

	std::string val1 = stack.back();
	stack.pop_back();
	std::string val2 = stack.back();
	stack.pop_back();

	stack.push_back(val2 + val1);
}
