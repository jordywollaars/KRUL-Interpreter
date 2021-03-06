#include "StringEnlOperation.hpp"

void StringEnlOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	if (stack.empty())
		throw std::exception("Nothing found on the stack");

	std::string val = stack.back();
	stack.pop_back();

	val += "\n";

	stack.push_back(val);
}
