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
	// Starts the UI
	void salesmanMenu();
	void makeNewOrder();
private:

	// Start by selecting pizza location
	bool selectLocation(Order& order, string& input);
	// Asks if user wants to make his own pizza or select from menu
	bool newOrderStart(Order& order, bool& pizzaFromMenu, string& input);
	// Picking pizzas from menu
	void pickFromMenu(Order& order, string& input);
	// Order menu
	void makeYourOwnMenu(Order& order, string& input, const bool& isFromMenu=false);
	// Pizza menu's
	void selectCrust(Order& order, string& input);
	void selectSize(Order& order, string& input);
	void selectToppings(Order& order, string& input);
	void selectSides(Order& order, string& input);
	// Order menu's 
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
	void showSingleSide(Order& order, const int& index, string& input);
	void deleteSide(Order& order, const int& index);
	// Finishing order
	void finishOrder(Order& order);
	
	// Use for try-catching input from user
	void catchStringInput(string& input, const int& max, const int& min=1, const std::string& msg="Input");
	int convertToInt(string& input);

	// Make a string vector for the printMenu functions
	// PizzaSize has a unique price modifier so we need a special function for it.
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