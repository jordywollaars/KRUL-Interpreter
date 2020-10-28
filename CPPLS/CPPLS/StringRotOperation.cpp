#include "StringRotOperation.hpp"

void StringRotOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	if (stack.empty())
		throw std::exception("Nothing found on the stack.");

	std::string val = stack.back();
	stack.pop_back();

	for (std::string::size_type len = val.length(), idx = 0; idx != len; ++idx) {
		if (val[idx] >= 'a' && val[idx] <= 'm') {
			val[idx] = val[idx] + 13;
		}
		else if (val[idx] >= 'n' && val[idx] <= 'z') {
			val[idx] = val[idx] - 13;
		}
		else if (val[idx] >= 'A' && val[idx] <= 'M') {
			val[idx] = val[idx] + 13;
		}
		else if (val[idx] >= 'N' && val[idx] <= 'Z') {
			val[idx] = val[idx] - 13;
		}
	}

	stack.push_back(val);
}
