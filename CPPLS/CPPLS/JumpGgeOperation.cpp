#include "JumpGgeOperation.hpp"

JumpGgeOperation::JumpGgeOperation(int& position) : currentPosition{position}
{
}

void JumpGgeOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	std::string label = stack.back();
	stack.pop_back();
	std::string val2 = stack.back();
	stack.pop_back();
	std::string val1 = stack.back();
	stack.pop_back();

	if (std::stoi(val1) >= std::stoi(val2))
	{
		this->currentPosition = std::stoi(label) - 1;
	}
}
