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
	int _pizzaNumber;
public:
	SalesmanUI();
	void salesmanMenu();
	void makeNewOrder();
private:
	void makeYourOwnMenu(Order& order, char& input);
	void selectLocation(Order& order, char& input);
	void newOrderStart(Order& order, bool& pizzaFromMenu, char& input);
	void pickFromMenu(Order& order, char& input);
	void selectCrust(Pizza& pizza, char& input);
	void selectSize(Pizza& pizza, char& input);
	void selectToppings(Pizza& pizza, char& input);
	void selectSides(Order& order, char& input);
	void addComment(Order& order);
	void selectDeliveryMethod(Order& order, char& input);
	bool addAnotherOrder(char& input);
	void showTotalOrder(Order& order);
	
	void catchCharInput(char& input, const int& max, const int& min=0, const std::string& msg="Input");

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