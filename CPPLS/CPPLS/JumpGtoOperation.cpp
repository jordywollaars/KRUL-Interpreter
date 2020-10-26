#include "JumpGtoOperation.hpp"

JumpGtoOperation::JumpGtoOperation(int& position) : currentPosition{position}
{
}

void JumpGtoOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	std::string label = stack.back();
	stack.pop_back();

	this->currentPosition = std::stoi(label) - 1;
}
