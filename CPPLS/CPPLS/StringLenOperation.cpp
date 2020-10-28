#include "StringLenOperation.hpp"

void StringLenOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	if (stack.empty())
		throw std::exception("Nothing found on the stack.");

	int len = stack.back().length();
	stack.pop_back();

	stack.push_back(std::to_string(len));
}
