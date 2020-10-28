#include "JumpGtoOperation.hpp"
#include "Utilities.hpp"

JumpGtoOperation::JumpGtoOperation(int& position) : currentPosition{position}
{
}

void JumpGtoOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	if (stack.empty())
		throw std::exception("Nothing on the stack to jump to.");

	std::string label = stack.back();
	stack.pop_back();

	if (!Utilities::isDigit(label))
		throw std::exception("Label could not be converted to an integer.");

	int labelAsInt = std::stoi(label);

	this->currentPosition = labelAsInt - 1;
}
