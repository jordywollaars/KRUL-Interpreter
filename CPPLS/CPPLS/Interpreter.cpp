#include "Interpreter.h"
#include <iostream>

//Interpreter::Interpreter(std::vector<std::string> newStack)
//{
//	this->instructions = newStack;
//}

Interpreter::Interpreter(std::string baseURL, std::string startFile) : baseURL{baseURL}
{
	this->loader = std::make_unique<Loader>();
	this->currentFile = startFile;
}

std::string Interpreter::startInterpreting()
{
	system("cls");

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

	system("cls");
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
	std::string instruction = this->instructions[position];
	const char type = this->instructions[position].at(0);

	if (type == ':')
	{
		return instruction;
	}

	if (type == '\\')
	{
		this->stack.push_back(instruction.substr(instruction.find("\\") + 1));
	}
	else if (type == '>')
	{
		this->stack.push_back(std::to_string(this->labelReferences[instruction.substr(instruction.find(">") + 1)]));
	}
	else if (type == '=')
	{
		this->variables[instruction.substr(instruction.find("=") + 1)] = this->stack.back();
		this->stack.pop_back();
	}
	else if (type == '$')
	{
		this->stack.push_back(this->variables[instruction.substr(instruction.find("$") + 1)]);
	}
	else
	{
		//String operations
		if (instruction == "dup")
		{
			this->stack.push_back(this->stack.back());
		}
		else if (instruction == "cat")
		{
			std::string val1 = this->stack.back();
			this->stack.pop_back();
			std::string val2 = this->stack.back();
			this->stack.pop_back();

			this->stack.push_back(val2 + val1);
		}
		else if (instruction == "rev")
		{
			std::string val1 = this->stack.back();
			this->stack.pop_back();

			int n = val1.length();

			for (int i = 0; i < n / 2; i++)
				std::swap(val1[i], val1[n - i - 1]);

			this->stack.push_back(val1);
		}
		else if (instruction == "idx")
		{
			int index = std::stoi(this->stack.back());
			this->stack.pop_back();
			std::string str = this->stack.back();
			this->stack.pop_back();

			std::string character = str.substr(index, 1);
			this->stack.push_back(character);
		}
		else if (instruction == "len")
		{
			int len = this->stack.back().length();
			this->stack.pop_back();

			this->stack.push_back(std::to_string(len));
		}
		else if (instruction == "slc")
		{
			int to = std::stoi(this->stack.back());
			this->stack.pop_back();
			int from = std::stoi(this->stack.back());
			this->stack.pop_back();
			std::string val = this->stack.back();
			this->stack.pop_back();

			std::string newVal = val.substr(from, (to - from));

			this->stack.push_back(newVal);
		}
		else if (instruction == "rot")
		{
			std::string val = this->stack.back();
			this->stack.pop_back();

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

			this->stack.push_back(val);
		}
		else if (instruction == "enl")
		{
			std::string val = this->stack.back();
			this->stack.pop_back();

			val += "\n";

			this->stack.push_back(val);
		}
		//Integer operations
		else if (instruction == "add")
		{
			int valAsInt1 = std::stoi(this->stack.back());
			this->stack.pop_back();
			int valAsInt2 = std::stoi(this->stack.back());
			this->stack.pop_back();

			this->stack.push_back(std::to_string(valAsInt1 + valAsInt2));
		}
		else if (instruction == "sub")
		{
			int valAsInt1 = std::stoi(this->stack.back());
			this->stack.pop_back();
			int valAsInt2 = std::stoi(this->stack.back());
			this->stack.pop_back();

			this->stack.push_back(std::to_string(valAsInt2 - valAsInt1));
		}
		else if (instruction == "dec")
		{
			int valAsInt = std::stoi(this->stack.back());
			this->stack.pop_back();
			valAsInt--;
			this->stack.push_back(std::to_string(valAsInt));
		}
		else if (instruction == "inc")
		{
			int valAsInt = std::stoi(this->stack.back());
			this->stack.pop_back();
			valAsInt++;
			this->stack.push_back(std::to_string(valAsInt));
		}
		else if (instruction == "mod")
		{
			int valAsInt1 = std::stoi(this->stack.back());
			this->stack.pop_back();
			int valAsInt2 = std::stoi(this->stack.back());
			this->stack.pop_back();

			this->stack.push_back(std::to_string(valAsInt2 % valAsInt1));
		}
		else if (instruction == "div")
		{
			int valAsInt1 = std::stoi(this->stack.back());
			this->stack.pop_back();
			int valAsInt2 = std::stoi(this->stack.back());
			this->stack.pop_back();

			this->stack.push_back(std::to_string(valAsInt2 / valAsInt1));
		}
		else if (instruction == "mul")
		{
			int valAsInt1 = std::stoi(this->stack.back());
			this->stack.pop_back();
			int valAsInt2 = std::stoi(this->stack.back());
			this->stack.pop_back();

			this->stack.push_back(std::to_string(valAsInt2 * valAsInt1));
		}
		else if (instruction == "neg")
		{
			int val = std::stoi(this->stack.back());
			this->stack.pop_back();

			int newVal = val * -1;

			this->stack.push_back(std::to_string(newVal));
		}
		else if (instruction == "abs")
		{
			int val = std::stoi(this->stack.back());
			this->stack.pop_back();

			int newVal = std::abs(val);

			this->stack.push_back(std::to_string(newVal));
		}
		//Tests & Jumps
		else if (instruction == "gto")
		{
			std::string label = this->stack.back();
			this->stack.pop_back();

			this->currentPosition = std::stoi(label) - 1;
		}
		else if (instruction == "gne")
		{
			std::string label = this->stack.back();
			this->stack.pop_back();
			std::string val2 = this->stack.back();
			this->stack.pop_back();
			std::string val1 = this->stack.back();
			this->stack.pop_back();

			if (val1 != val2)
			{
				this->currentPosition = std::stoi(label) - 1;
			}
		}
		else if (instruction == "gge")
		{
			std::string label = this->stack.back();
			this->stack.pop_back();
			std::string val2 = this->stack.back();
			this->stack.pop_back();
			std::string val1 = this->stack.back();
			this->stack.pop_back();

			if (std::stoi(val1) >= std::stoi(val2))
			{
				this->currentPosition = std::stoi(label) - 1;
			}
		}
		else if (instruction == "ggt")
		{
			std::string label = this->stack.back();
			this->stack.pop_back();
			std::string val2 = this->stack.back();
			this->stack.pop_back();
			std::string val1 = this->stack.back();
			this->stack.pop_back();

			if (std::stoi(val1) > std::stoi(val2))
			{
				this->currentPosition = std::stoi(label) - 1;
			}
		}
		else if (instruction == "gle")
		{
			std::string label = this->stack.back();
			this->stack.pop_back();
			std::string val2 = this->stack.back();
			this->stack.pop_back();
			std::string val1 = this->stack.back();
			this->stack.pop_back();

			if (std::stoi(val1) <= std::stoi(val2))
			{
				this->currentPosition = std::stoi(label) - 1;
			}
		}
		else if (instruction == "glt")
		{
			std::string label = this->stack.back();
			this->stack.pop_back();
			std::string val2 = this->stack.back();
			this->stack.pop_back();
			std::string val1 = this->stack.back();
			this->stack.pop_back();

			if (std::stoi(val1) < std::stoi(val2))
			{
				this->currentPosition = std::stoi(label) - 1;
			}
		}
		//Functies
		else if (instruction == "ret")
		{
			int loc = std::stoi(this->callStack.back());
			this->callStack.pop_back();

			this->currentPosition = loc - 1;
		}
		else if (instruction == "fun")
		{
			this->callStack.push_back(std::to_string(this->currentPosition + 1));

			//TODO: Temp gto code under here
			std::string label = this->stack.back();
			this->stack.pop_back();

			this->currentPosition = std::stoi(label) - 1;
		}
		//EndOfSearch
		else if (instruction == "end")
		{
			//
		}
		//Digit
		else
		{
			this->stack.push_back(instruction);
		}
	}

	return instruction;
}
