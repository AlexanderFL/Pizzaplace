#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Order.h"

using namespace std;
class CommonUI
{
public:
	//Clears the screen
	void clear() const;

	//Prints a menu to the screen with the options in it
	void printMenu(const vector<string>& options) const;
	//Prints a menu to the screen with the options in it and a title
	void printMenu(const vector<string>& options, const string& title, const bool& displayOnly=false) const;
	//Prints an arrow with the string
	void printArrow(const string& str) const;
	//Prints a meesage with the string
	void printMessage(const string& str) const;

	/*	Get Functions	*/
	//Gets the input from the user
	void getInput(string& str) const;
	//Gets the input from the user with custom text
	void getInput(const string& text, string& str) const;
	//Gets the input from the user with custom text, char edtion
	void getInput(const string& text, char& input) const;

	/*		Printing info		*/	
	//Prints info about a pizza in a short format
	void showPizzaInfoShort(const Pizza& pizza) const;
	//Prints info about a order
	void showOrderInfo(const Order& order) const;
	//Prints info about a order in a short format
	void showOrderInfoShort(const Order& order) const;

private:
	//Prints the menu with the options
	void printOptions(const vector<string>& options, size_t biggest, bool displayOnly=false) const;
	//Prints lines
	void printLines(size_t size) const;
	//Finds the biggest string size from the vector
	size_t biggestStringSize(const vector<string>& vec) const;
};