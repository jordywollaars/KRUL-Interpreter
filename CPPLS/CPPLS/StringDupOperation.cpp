#include "StringDupOperation.hpp"

void StringDupOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	if (stack.empty())
		throw std::exception("Nothing on the stack to duplicate.");

	stack.push_back(stack.back());
}
