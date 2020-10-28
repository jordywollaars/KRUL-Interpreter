#include "IntegerModOperation.hpp"
#include "Utilities.hpp"

void IntegerModOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{

	if (stack.size() < 2)
		throw std::exception("Nothing on the stack.");

	if (!Utilities::isDigit(stack.back()))
		throw std::exception("Value could not be converted to an integer.");

	int valAsInt1 = std::stoi(stack.back());
	stack.pop_back();

	if (!Utilities::isDigit(stack.back()))
		throw std::exception("Value could not be converted to an integer.");

	int valAsInt2 = std::stoi(stack.back());
	stack.pop_back();

	if (valAsInt1 == 0)
	{
		throw std::exception("Modulo by 0 is impossible");
	}

	stack.push_back(std::to_string(valAsInt2 % valAsInt1));
}
