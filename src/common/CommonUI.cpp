#include "CommonUI.h"

string CommonUI::printMenu(const vector<string>& options)
{
	string output = "";
	output += printOptions(options, biggestStringSize(options));
	return output;
}

string CommonUI::printMenu(const vector<string>& options, const string& title) {
	string output = "";
	vector<string> temp = options;
	temp.push_back(title);
	size_t biggest = biggestStringSize(temp);
	output += printLines(biggest);
	output += "\t| ";
	output += title;
	for (size_t j = 0; j < ((biggest * 2) - title.size()); j++) {
		output += " ";
	}
	output += "          |\n";
	output += printOptions(options, biggest);
	return output;
}

string CommonUI::printInput(const string& str) {
	string output = "\t|\n\t-->";
	output += str;
	output += ": ";
	return output;
}

string CommonUI::printMessage(const string& str) {
	string output = "\t";
	for (unsigned int i = 0; i < str.size() + 4; i++) {
		output += "-";
	}
	output += "\n\t| ";
	output += str;
	output += " |\n\t";
	for (unsigned int i = 0; i < str.size() + 4; i++) {
		output += "-";
	}
	return output;
}

//Private functions

//print out minus signs (for lines)
string CommonUI::printLines(unsigned int size)
{
	string output = "";
	output += "\t";
	for (unsigned int i = 0; i < size * 2; i++) {
		output += "-";
	}
	output += "-------------\n";
	return output;
}

string CommonUI::printOptions(const vector<string>& options, size_t biggest) {
	string output = "";
	for (size_t i = 0; i < options.size(); i++) {
		output += printLines(biggest);
		output += "\t| ";
		output += to_string(i + 1);
		output += ". ";
		output += options.at(i);
		for (size_t j = 0; j < (biggest - options.at(i).size()); j++) {
			output += " ";
		}
		output += " | ";
		i++;

		//if there is an odd number of options, then the last box needs to be empty
		if (options.size() == i) {
			output += "   ";
			for (size_t j = 0; j < biggest; j++) {
				output += " ";
			}
		}
		else {
			output += to_string(i + 1);
			output += ". ";
			output += options.at(i);
			for (size_t j = 0; j < (biggest - options.at(i).size()); j++) {
				output += " ";
			}
		}
		output += " |\n";
	}
	output += printLines(biggest);
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