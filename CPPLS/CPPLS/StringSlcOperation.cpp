#include "StringSlcOperation.hpp"

void StringSlcOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	int to = std::stoi(stack.back());
	stack.pop_back();
	int from = std::stoi(stack.back());
	stack.pop_back();
	std::string val = stack.back();
	stack.pop_back();

	std::string newVal = val.substr(from, (to - from));

	stack.push_back(newVal);
}
