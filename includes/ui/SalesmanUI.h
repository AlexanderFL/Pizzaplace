#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include "CommonUI.h"
#include "SalesmanService.h"
using namespace std;

class SalesmanUI: public CommonUI
{
private:
	SalesmanService service;
public:
	SalesmanUI();
	void salesmanMenu();
	void makeNewOrder();
	void pickFromMenu();
private:
	void selectLocation(Order& order, char& input);
	void selectFromMenu(bool& pizzaFromMenu, char& input);
	void selectCrust(Pizza& pizza, char& input);
	void selectSize(Pizza& pizza, char& input);
	void selectToppings(Pizza& pizza, char& input);
	void selectSides(Order& order, char& input);
	void addComment(Order& order, char& input);
	bool addAnotherOrder(char& input);
	
	vector<string> makeStringVectorFromPizzaSize(vector<PizzaSize> pizzaSizeVector);

	template<typename T>
	vector<string> makeStringVector(T tempVector);
};

template<typename T>
vector<string> SalesmanUI::makeStringVector(T tempVector)
{
	vector<string> tmpReturnString;

	string tempString;
	for (size_t i = 0; i < tempVector.size(); i++) {
		tempString = tempVector.at(i).getName();
		tempString += " | ";
		tempString += to_string(tempVector.at(i).getPrice());
		tempString += " kr.-";

		tmpReturnString.push_back(tempString);
	}
	return tmpReturnString;
}