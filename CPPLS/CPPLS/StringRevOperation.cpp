#include "StringRevOperation.hpp"

void StringRevOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	std::string val1 = stack.back();
	stack.pop_back();

	int n = val1.length();

	for (int i = 0; i < n / 2; i++)
		std::swap(val1[i], val1[n - i - 1]);

	stack.push_back(val1);
}
