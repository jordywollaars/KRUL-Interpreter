#include "IntegerSubOperation.hpp"

void IntegerSubOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	int valAsInt1 = std::stoi(stack.back());
	stack.pop_back();
	int valAsInt2 = std::stoi(stack.back());
	stack.pop_back();

	stack.push_back(std::to_string(valAsInt2 - valAsInt1));
}
