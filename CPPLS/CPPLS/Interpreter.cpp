#include <iostream>
#include "Interpreter.hpp"
#include "IInstruction.hpp"
#include "StringDupOperation.hpp"
#include "StringCatOperation.hpp"
#include "StringRevOperation.hpp"
#include "StringIdxOperation.hpp"
#include "StringLenOperation.hpp"
#include "StringSlcOperation.hpp"
#include "StringRotOperation.hpp"
#include "StringEnlOperation.hpp"
#include "IntegerAddOperation.hpp"
#include "IntegerSubOperation.hpp"
#include "IntegerDecOperation.hpp"
#include "IntegerIncOperation.hpp"
#include "IntegerModOperation.hpp"
#include "IntegerDivOperation.hpp"
#include "IntegerMulOperation.hpp"
#include "IntegerNegOperation.hpp"
#include "IntegerAbsOperation.hpp"
#include "JumpGtoOperation.hpp"
#include "JumpGneOperation.hpp"
#include "JumpGgeOperation.hpp"
#include "JumpGgtOperation.hpp"
#include "JumpGleOperation.hpp"
#include "JumpGltOperation.hpp"
#include "FunctieFunOperation.hpp"
#include "FunctieRetOperation.hpp"
#include "Utilities.hpp"

Interpreter::Interpreter(std::string baseURL, std::string startFile) : baseURL{ baseURL }
{
	this->loader = std::make_unique<Loader>();
	this->currentFile = startFile;
}

std::string Interpreter::startInterpreting()
{
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Current address: " << std::endl << this->baseURL << this->currentFile << std::endl;
	this->instructions = loader.get()->LoadInstructionsFromURL(this->baseURL + this->currentFile);

	setupPrequirements();

	std::string output;
	for (this->currentPosition; this->currentPosition < this->instructions.size(); this->currentPosition++)
	{
		output = this->interpret(this->currentPosition);

		if (output == "error")
		{
			return "Error: The program has crashed due to an error!";
		}
	}

	std::string result;
	result = this->stack.back();
	this->stack.pop_back();

	if (output == "end")
	{
		result = "Message found: \n" + result;
		return result;
	}

	//std::cout << SECTIONDIVIDER << std::endl;
	std::cout << "Result:" << std::endl << result << std::endl;
	system("pause");
	this->currentFile = result;
	return this->startInterpreting();
}

void Interpreter::setupPrequirements()
{
	this->labelReferences = std::map<std::string, int>();
	this->variables = std::map<std::string, std::string>();
	this->callStack = std::vector<std::string>();
	this->stack = std::vector<std::string>();
	this->currentPosition = 0;

	for (this->currentPosition; this->currentPosition < this->instructions.size() - 1; this->currentPosition++)
	{
		std::string instruction = this->instructions[this->currentPosition];
		const char type = this->instructions[this->currentPosition].at(0);

		if (type == ':')
		{
			this->labelReferences[instruction.substr(instruction.find(":") + 1)] = this->currentPosition + 1;
		}
	}
	this->currentPosition = 0;
}

std::string Interpreter::interpret(int position)
{
	const std::string instruction = this->instructions[position];
	const char type = instruction.at(0);

	if (instruction.substr(0, 1) == ":" || instruction == "end")
	{
		return instruction;
	}

	std::string key;
	switch (type)
	{
	case '\\':
		this->stack.push_back(instruction.substr(instruction.find("\\") + 1));
		return instruction;
	case '>':
		key = instruction.substr(instruction.find(">") + 1);
		if (this->labelReferences.find(key) != this->labelReferences.end())
		{
			this->stack.push_back(std::to_string(this->labelReferences[key]));
			return instruction;
		}
		std::cout << "Exception at line(" << this->currentPosition << "): " << "Label '"<< key <<"' doesn't exist" << std::endl;
		return "error";
	case '=':
		if (this->stack.empty())
		{
			std::cout << "Exception at line(" << this->currentPosition << "): " << "Nothing found on the stack" << std::endl;
			return "error";
		}
		this->variables[instruction.substr(instruction.find("=") + 1)] = this->stack.back();
		this->stack.pop_back();
		return instruction;
	case '$':
		key = instruction.substr(instruction.find("$") + 1);
		if (this->variables.find(key) != this->variables.end())
		{
			this->stack.push_back(this->variables[key]);
			return instruction;
		}
		std::cout << "Exception at line(" << this->currentPosition << "): " << "Variable '" << key << "' doesn't exist" << std::endl;
		return "error";
	default:
		break;
	}

	if (Utilities::isDigit(instruction))
	{
		this->stack.push_back(instruction);
		return instruction;
	}

	try
	{
		std::unique_ptr<IInstruction> instructionOperator = getOperation(instruction);
		instructionOperator->execute(this->stack, this->callStack, this->variables, this->labelReferences);
		return instruction;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Exception at line(" << this->currentPosition << "): " << ex.what() << std::endl;
		return "error";
	}
}

std::unique_ptr<IInstruction> Interpreter::getOperation(std::string op)
{
	std::unique_ptr<IInstruction> operation;

	//String operations
	if (op == "dup")
	{
		operation = std::make_unique<StringDupOperation>();
	}
	else if (op == "cat")
	{
		operation = std::make_unique<StringCatOperation>();
	}
	else if (op == "rev")
	{
		operation = std::make_unique<StringRevOperation>();
	}
	else if (op == "idx")
	{
		operation = std::make_unique<StringIdxOperation>();
	}
	else if (op == "len")
	{
		operation = std::make_unique<StringLenOperation>();
	}
	else if (op == "slc")
	{
		operation = std::make_unique<StringSlcOperation>();
	}
	else if (op == "rot")
	{
		operation = std::make_unique<StringRotOperation>();
	}
	else if (op == "enl")
	{
		operation = std::make_unique<StringEnlOperation>();
	}
	//Integer operations
	else if (op == "add")
	{
		operation = std::make_unique<IntegerAddOperation>();
	}
	else if (op == "sub")
	{
		operation = std::make_unique<IntegerSubOperation>();
	}
	else if (op == "dec")
	{
		operation = std::make_unique<IntegerDecOperation>();
	}
	else if (op == "inc")
	{
		operation = std::make_unique<IntegerIncOperation>();
	}
	else if (op == "mod")
	{
		operation = std::make_unique<IntegerModOperation>();
	}
	else if (op == "div")
	{
		operation = std::make_unique<IntegerDivOperation>();
	}
	else if (op == "mul")
	{
		operation = std::make_unique<IntegerMulOperation>();
	}
	else if (op == "neg")
	{
		operation = std::make_unique<IntegerNegOperation>();
	}
	else if (op == "abs")
	{
		operation = std::make_unique<IntegerAbsOperation>();
	}
	//Tests & Jumps
	else if (op == "gto")
	{
		operation = std::make_unique<JumpGtoOperation>(this->currentPosition);
	}
	else if (op == "gne")
	{
		operation = std::make_unique<JumpGneOperation>(this->currentPosition);
	}
	else if (op == "gge")
	{
		operation = std::make_unique<JumpGgeOperation>(this->currentPosition);
	}
	else if (op == "ggt")
	{
		operation = std::make_unique<JumpGgtOperation>(this->currentPosition);
	}
	else if (op == "gle")
	{
		operation = std::make_unique<JumpGleOperation>(this->currentPosition);
	}
	else if (op == "glt")
	{
		operation = std::make_unique<JumpGltOperation>(this->currentPosition);
	}
	//Functies
	else if (op == "ret")
	{
		operation = std::make_unique<FunctieRetOperation>(this->currentPosition);
	}
	else if (op == "fun")
	{
		operation = std::make_unique<FunctieFunOperation>(this->currentPosition);
	}

	if (operation)
	{
		return operation;
	}

	std::string exceptionMessage = "Unknown operation(" + op + ")";
	throw std::exception(exceptionMessage.c_str());
}
