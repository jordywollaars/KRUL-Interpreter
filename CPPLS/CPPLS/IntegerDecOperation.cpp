#include "IntegerDecOperation.hpp"
#include "Utilities.hpp"

void IntegerDecOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	if (stack.empty())
		throw std::exception("Nothing on the stack.");

	if (!Utilities::isDigit(stack.back()))
		throw std::exception("Value could not be converted to an integer.");

	int valAsInt = std::stoi(stack.back());
	stack.pop_back();
	valAsInt--;
	stack.push_back(std::to_string(valAsInt));
}
