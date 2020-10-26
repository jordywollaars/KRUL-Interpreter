#pragma once
#include "IInstruction.h"
class JumpGgeOperation :
	public IInstruction
{
private:
	int& currentPosition;
public:
	JumpGgeOperation(int& position);
	// Inherited via IInstruction
	virtual void execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences) override;
};

