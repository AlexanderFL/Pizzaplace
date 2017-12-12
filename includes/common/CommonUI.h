#pragma once
#include <string>
#include <vector>

using namespace std;
class CommonUI
{
public:
	string printMenu(vector<string> options);
private:
	string printLines(unsigned int size);
};

