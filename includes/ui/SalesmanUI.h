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
	void makeYourOwnMenu(Order& order, string& input);

	void selectLocation(Order& order, string& input);
	void newOrderStart(Order& order, bool& pizzaFromMenu, string& input);
	void pickFromMenu(Order& order, string& input);
	void selectCrust(Order& order, string& input);
	void selectSize(Order& order, string& input);
	void selectToppings(Order& order, string& input);
	void selectSides(Order& order, string& input);
	void addComment(Order& order);
	void selectDeliveryMethod(Order& order, string& input);
	void addAnotherPizza(Order& order);
	// Viewing and editing Order
	void showTotalOrder(Order& order, string& input);
	// Viewing and editing a single pizza
	void showSinglePizza(Order& order, const int& index, string& input);
	void showToppings(Pizza& pizza, string& input);
	void showCrust(Pizza& pizza, string& input);
	void showSize(Pizza& pizza, string& input);
	void selectPizza(const int& index);
	void deletePizza(Order& order, const int& index);
	// Viewing and editing side orders
	void showSides(Order& order, string& input);
	// Finishing order
	void finishOrder(Order& order);
	
	void catchStringInput(string& input, const int& max, const int& min=1, const std::string& msg="Input");
	Pizza getCurrentPizza(Order& order);
	int convertToInt(string& input);


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