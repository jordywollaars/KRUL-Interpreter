#include "Interpreter.h"
#include <iostream>
#include "IInstruction.h"
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

Interpreter::Interpreter(std::string baseURL, std::string startFile) : baseURL{ baseURL }
{
	this->loader = std::make_unique<Loader>();
	this->currentFile = startFile;
}

std::string Interpreter::startInterpreting()
{

	this->instructions = loader.get()->LoadInstructionsFromURL(this->baseURL + this->currentFile);

	setupPrequirements();

	std::string output;
	for (this->currentPosition; this->currentPosition < this->instructions.size(); this->currentPosition++)
	{
		output = this->interpret(this->currentPosition);
		//std::cout << output << std::endl;
	}

	std::string result;
	result = this->stack.back();
	this->stack.pop_back();

	if (output == "end")
	{
		return result;
	}

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
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
	std::unique_ptr<IInstruction> instructionOperator;

	if (instruction.substr(0, 1) == ":" || instruction == "end")
	{
		return instruction;
	}

	if (instruction.substr(0, 1) == "\\")
	{
		this->stack.push_back(instruction.substr(instruction.find("\\") + 1));
	}
	else if (instruction.substr(0, 1) == ">")
	{
		this->stack.push_back(std::to_string(this->labelReferences[instruction.substr(instruction.find(">") + 1)]));
	}
	else if (instruction.substr(0, 1) == "=")
	{
		this->variables[instruction.substr(instruction.find("=") + 1)] = this->stack.back();
		this->stack.pop_back();
	}
	else if (instruction.substr(0, 1) == "$")
	{
		this->stack.push_back(this->variables[instruction.substr(instruction.find("$") + 1)]);
	}
	else
	{
		//String operations
		if (instruction == "dup")
		{
			instructionOperator = std::make_unique<StringDupOperation>();
		}
		else if (instruction == "cat")
		{
			instructionOperator = std::make_unique<StringCatOperation>();
		}
		else if (instruction == "rev")
		{
			instructionOperator = std::make_unique<StringRevOperation>();
		}
		else if (instruction == "idx")
		{
			instructionOperator = std::make_unique<StringIdxOperation>();
		}
		else if (instruction == "len")
		{
			instructionOperator = std::make_unique<StringLenOperation>();
		}
		else if (instruction == "slc")
		{
			instructionOperator = std::make_unique<StringSlcOperation>();
		}
		else if (instruction == "rot")
		{
			instructionOperator = std::make_unique<StringRotOperation>();
		}
		else if (instruction == "enl")
		{
			instructionOperator = std::make_unique<StringEnlOperation>();
		}
		//Integer operations
		else if (instruction == "add")
		{
			instructionOperator = std::make_unique<IntegerAddOperation>();
		}
		else if (instruction == "sub")
		{
			instructionOperator = std::make_unique<IntegerSubOperation>();
		}
		else if (instruction == "dec")
		{
			instructionOperator = std::make_unique<IntegerDecOperation>();
		}
		else if (instruction == "inc")
		{
			instructionOperator = std::make_unique<IntegerIncOperation>();
		}
		else if (instruction == "mod")
		{
			instructionOperator = std::make_unique<IntegerModOperation>();
		}
		else if (instruction == "div")
		{
			instructionOperator = std::make_unique<IntegerDivOperation>();
		}
		else if (instruction == "mul")
		{
			instructionOperator = std::make_unique<IntegerMulOperation>();
		}
		else if (instruction == "neg")
		{
			instructionOperator = std::make_unique<IntegerNegOperation>();
		}
		else if (instruction == "abs")
		{
			instructionOperator = std::make_unique<IntegerAbsOperation>();
		}
		//Tests & Jumps
		else if (instruction == "gto")
		{
			instructionOperator = std::make_unique<JumpGtoOperation>(this->currentPosition);

		}
		else if (instruction == "gne")
		{
			instructionOperator = std::make_unique<JumpGneOperation>(this->currentPosition);

		}
		else if (instruction == "gge")
		{
			instructionOperator = std::make_unique<JumpGgeOperation>(this->currentPosition);
		}
		else if (instruction == "ggt")
		{
			instructionOperator = std::make_unique<JumpGgtOperation>(this->currentPosition);
		}
		else if (instruction == "gle")
		{
			instructionOperator = std::make_unique<JumpGleOperation>(this->currentPosition);
		}
		else if (instruction == "glt")
		{
			instructionOperator = std::make_unique<JumpGltOperation>(this->currentPosition);
		}
		//Functies
		else if (instruction == "ret")
		{
			instructionOperator = std::make_unique<FunctieRetOperation>(this->currentPosition);
		}
		else if (instruction == "fun")
		{
			instructionOperator = std::make_unique<FunctieFunOperation>(this->currentPosition);
		}
		//Digit
		else
		{
			this->stack.push_back(instruction);
		}

		if (instructionOperator.get())
		{
			instructionOperator->execute(this->stack, this->callStack, this->variables, this->labelReferences);
		}

	}

	return instruction;
}
