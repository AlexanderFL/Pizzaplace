#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class CommonUI
{
public:
	void clear() const;
	void printMenu(const vector<string>& options) const;
	void printMenu(const vector<string>& options, const string& title) const;
	void printInput(const string& str) const;
	void printMessage(const string& str) const;
	void getInput(string& str) const;
private:
	void printOptions(const vector<string>& options, size_t biggest) const;
	void printLines(size_t size) const;
	size_t biggestStringSize(const vector<string>& vec) const;
};

