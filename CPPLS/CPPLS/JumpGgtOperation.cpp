#include "JumpGgtOperation.hpp"
#include "Utilities.hpp"

JumpGgtOperation::JumpGgtOperation(int& position) : currentPosition{position}
{
}

void JumpGgtOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	if (stack.size() < 3)
		throw std::exception("Not enough values on the stack");

	if (!Utilities::isDigit(stack.back()))
		throw std::exception("Label could not be converted to an integer.");

	int label = std::stoi(stack.back());
	stack.pop_back();

	if (!Utilities::isDigit(stack.back()))
		throw std::exception("Value could not be converted to an integer.");

	int val2 = std::stoi(stack.back());
	stack.pop_back();

	if (!Utilities::isDigit(stack.back()))
		throw std::exception("Value could not be converted to an integer.");

	int val1 = std::stoi(stack.back());
	stack.pop_back();

	if (val1 > val2)
	{
		this->currentPosition = label - 1;
	}
}
