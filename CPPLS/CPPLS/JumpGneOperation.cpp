#include "JumpGneOperation.hpp"

JumpGneOperation::JumpGneOperation(int& position) : currentPosition{position}
{
}

void JumpGneOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	std::string label = stack.back();
	stack.pop_back();
	std::string val2 = stack.back();
	stack.pop_back();
	std::string val1 = stack.back();
	stack.pop_back();

	if (val1 != val2)
	{
		this->currentPosition = std::stoi(label) - 1;
	}
}
