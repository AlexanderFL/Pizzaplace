#include "CommonUI.h"
#include <stdlib.h>

void CommonUI::clear() const {
	system("CLS");
}

void CommonUI::printMenu(const vector<string>& options) const {
	printOptions(options, biggestStringSize(options));
}

void CommonUI::printMenu(const vector<string>& options, const string& title, const bool& displayOnly) const {
	vector<string> temp = options;
	temp.push_back(title);
	size_t biggest = biggestStringSize(temp);
	printLines(biggest);
	cout << "\t| " << title;
	for (size_t j = 0; j < ((biggest * 2) - title.size()); j++) {
		cout << " ";
	}
	cout << "          |\n";
	printOptions(options, biggest, displayOnly);
}

void CommonUI::printInput(const string& str) const {
	cout << "\t|\n\t-->" << str << ": ";
}

void CommonUI::printMessage(const string& str) const {
	cout << "\t";
	for (unsigned int i = 0; i < str.size() + 4; i++) {
		cout << "-";
	}
	cout << "\n\t| " << str << " |\n\t";
	for (unsigned int i = 0; i < str.size() + 4; i++) {
		cout << "-";
	}
	cout << endl;
}

void CommonUI::getInput(string& str) const {
	printInput("Input");
	cin >> ws; 
	getline(cin, str);
}

void CommonUI::getInput(const string& text, string& str) const {
	printInput(text);
	cin >> ws;
	getline(cin, str);
}

void CommonUI::getInput(const string& text, char & input) const
{
	printInput(text);
	cin >> input;
	cin.ignore();
}

//Private functions

//print out minus signs (for lines)
void CommonUI::printLines(size_t size) const {
	cout << "\t";
	for (unsigned int i = 0; i < size * 2; i++) {
		cout << "-";
	}
	cout << "-------------\n";
}

void CommonUI::printOptions(const vector<string>& options, size_t biggest, bool displayOnly) const {
	for (size_t i = 0; i < options.size(); i++) {
		printLines(biggest);
		if (!displayOnly) {
			cout << "\t| " << i + 1 << ". " << options.at(i);
		}
		else {
			cout << "\t| " << options.at(i);
		}
		for (size_t j = 0; j < (biggest - options.at(i).size()); j++) {
			cout << " ";
		}
		cout << " | ";
		i++;

		//if there is an odd number of options, then the last box needs to be empty
		if (options.size() == i) {
			cout << "   ";
			for (size_t j = 0; j < biggest; j++) {
				cout << " ";
			}
			if (displayOnly) {
				cout << "   ";
			}
		}
		else {
			if (!displayOnly) {
				cout << i + 1 << ". " << options.at(i);
			}
			else {
				cout << options.at(i) << "\t   ";
			}
			for (size_t j = 0; j < (biggest - options.at(i).size()); j++) {
				cout << " ";
			}
		}
		cout << " |\n";
	}
	printLines(biggest);
}

size_t CommonUI::biggestStringSize(const vector<string>& vec) const {
	size_t biggest = 0;
	for (size_t i = 0; i < vec.size(); i++) {
		if (biggest < vec.at(i).size()) {
			biggest = vec.at(i).size();
		}
	}
	return biggest;
}