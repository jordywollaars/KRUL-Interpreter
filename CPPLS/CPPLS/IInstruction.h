#pragma once
#include <vector>
#include <string>
#include <map>

class IInstruction {
public:
	virtual void execute(
		std::vector<std::string>& stack,
		std::vector<std::string>& callStack,
		std::map<std::string, std::string>& variables,
		std::map<std::string, int>& labelReferences) = 0;
};