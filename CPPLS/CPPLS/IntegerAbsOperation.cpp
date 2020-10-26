#include "IntegerAbsOperation.hpp"

void IntegerAbsOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	int val = std::stoi(stack.back());
	stack.pop_back();

	int newVal = std::abs(val);

	stack.push_back(std::to_string(newVal));
}
