#include "Menu.h"


string Menu::printMenu(vector<string> options)
{
	string biggestString = "";
	for (unsigned int i = 0; i < options.size(); i++)
	{
		if (biggestString.size() < options.at(i).size())
		{
			biggestString = options.at(i);
		}
	}
	string output = "";
	for (unsigned int i = 0; i < options.size(); i++)
	{
		output += printLines(biggestString.size());
		output += "\t| ";
		output += to_string(i + 1);
		output += ". ";
		output += options.at(i);
		for (unsigned int j = 0; j < (biggestString.size() - options.at(i).size()); j++)
		{
			output += " ";
		}
		output += " | ";
		i++;

		//if there is an odd number of options, then the last box needs to be empty
		if (options.size() == i)
		{
			output += "   ";
			for (unsigned int j = 0; j < biggestString.size(); j++)
			{
				output += " ";
			}
		}
		else
		{
			output += to_string(i + 1);
			output += ". ";
			output += options.at(i);
			for (unsigned int j = 0; j < (biggestString.size() - options.at(i).size()); j++)
			{
				output += " ";
			}
		}
		output += " |\n";
	}
	output += printLines(biggestString.size());
	return output;
}

//print out minus signs (for lines)
string Menu::printLines(unsigned int size)
{
	string output = "";
	output += "\t";
	for (unsigned int i = 0; i < size * 2; i++)
	{
		output += "-";
	}
	output += "-------------\n";
	return output;
}

