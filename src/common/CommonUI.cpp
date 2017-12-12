#include "CommonUI.h"


string CommonUI::printMenu(const vector<string>& options)
{
	size_t biggest = biggestStringSize(options);
	string output = "\n";
	for (unsigned int i = 0; i < options.size(); i++)
	{
		output += printLines(biggest);
		output += "\t| ";
		output += to_string(i + 1);
		output += ". ";
		output += options.at(i);
		for (unsigned int j = 0; j < (biggest - options.at(i).size()); j++) {
			output += " ";
		}
		output += " | ";
		i++;

		//if there is an odd number of options, then the last box needs to be empty
		if (options.size() == i) {
			output += "   ";
			for (unsigned int j = 0; j < biggest; j++) {
				output += " ";
			}
		}
		else {
			output += to_string(i + 1);
			output += ". ";
			output += options.at(i);
			for (unsigned int j = 0; j < (biggest - options.at(i).size()); j++) {
				output += " ";
			}
		}
		output += " |\n";
	}
	output += printLines(biggest);
	return output;
}

//print out minus signs (for lines)
string CommonUI::printLines(unsigned int size)
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

size_t CommonUI::biggestStringSize(const vector<string>& vec) {
	size_t biggest = 0;
	for (size_t i = 0; i < vec.size(); i++) {
		if (biggest < vec.at(i).size()) {
			biggest = vec.at(i).size();
		}
	}
	return biggest;
}