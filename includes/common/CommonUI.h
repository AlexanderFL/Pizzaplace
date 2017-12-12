#pragma once
#include <string>
#include <vector>

using namespace std;
class CommonUI
{
public:
	string printMenu(const vector<string>& options);
	string printMenu(const vector<string>& options, const string& title);
private:
	string printOptions(const vector<string>& options, size_t biggest);
	string printLines(unsigned int size);
	size_t biggestStringSize(const vector<string>& vec);
};

