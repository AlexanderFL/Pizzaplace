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
	void printMenu(const vector<string>& options, const string& title, const bool& displayOnly=false) const;
	void printArrow(const string& str) const;
	void printMessage(const string& str) const;
	void getInput(string& str) const;
	void getInput(const string& text, string& str) const;
	void getInput(const string& text, char& input) const;
private:
	void printOptions(const vector<string>& options, size_t biggest, bool displayOnly=false) const;
	void printLines(size_t size) const;
	size_t biggestStringSize(const vector<string>& vec) const;
};