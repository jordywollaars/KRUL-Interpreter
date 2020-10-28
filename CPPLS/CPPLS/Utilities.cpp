#include "Utilities.hpp"
#include <cctype>

bool Utilities::isDigit(std::string str)
{
	int i = 0;

	if(str.substr(0,1) == "-")
	{
		i++;
	}

	for (i; i < str.size(); i++)
	{
		if (!std::isdigit(str.at(i)))
		{
			return false;
		}
	}
	return true;
}
