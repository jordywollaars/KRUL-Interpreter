#pragma once
#include "IInstruction.h"
class JumpGneOperation :
	public IInstruction
{
private:
	int& currentPosition;
public:
	JumpGneOperation(int& position);
	// Inherited via IInstruction
	virtual void execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences) override;
};

