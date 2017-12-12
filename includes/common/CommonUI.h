#pragma once
#include <string>
#include <vector>

using namespace std;
class CommonUI
{
public:
	string printMenu(const vector<string>& options);
private:
	string printLines(unsigned int size);
	size_t biggestStringSize(const vector<string>& vec);
};

