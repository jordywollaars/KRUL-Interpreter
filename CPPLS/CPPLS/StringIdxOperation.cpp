#include "StringIdxOperation.hpp"

void StringIdxOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	int index = std::stoi(stack.back());
	stack.pop_back();
	std::string str = stack.back();
	stack.pop_back();

	std::string character = str.substr(index, 1);
	stack.push_back(character);
}
