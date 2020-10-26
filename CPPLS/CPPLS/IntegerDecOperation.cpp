#include "IntegerDecOperation.hpp"

void IntegerDecOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	int valAsInt = std::stoi(stack.back());
	stack.pop_back();
	valAsInt--;
	stack.push_back(std::to_string(valAsInt));
}
