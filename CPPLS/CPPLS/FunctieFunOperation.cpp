#include "FunctieFunOperation.hpp"
#include <memory>
#include "JumpGtoOperation.hpp"

FunctieFunOperation::FunctieFunOperation(int& position) :currentPosition{ position }
{
}

void FunctieFunOperation::execute(std::vector<std::string>& stack, std::vector<std::string>& callStack, std::map<std::string, std::string>& variables, std::map<std::string, int>& labelReferences)
{
	callStack.push_back(std::to_string(this->currentPosition + 1));

	std::unique_ptr<JumpGtoOperation> operation = std::make_unique<JumpGtoOperation>(this->currentPosition);
	operation->execute(stack, callStack, variables, labelReferences);
}
