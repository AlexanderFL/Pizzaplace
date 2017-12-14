#pragma once

#include <iostream>
#include <string>
#include "CommonService.h"
#include "Offer.h"
#include "InvalidOrder.h"
#include "InvalidAddress.h"
#include "InvalidInput.h"
using namespace std;

class SalesmanService: public CommonService
{
private:
	Data _repo;
	Pizza _pizza;
	SideOrder _sides;
public:
	SalesmanService();
	void registerNewOrder(Order& order);
	void appendToOrder(Order& firstOrder, Order& secondOrder);
	void appendToOrder(Order& firstOrder, Pizza& pizza);
	void appendToOrder(Order& order, SideOrder& sideAppend);
	int getPriceOfOrder(Order& order);
	int getOldPriceOfOrder(Order& order);
	void assignHomeAddress(Order& order, string address);
	void setOrderToDelivery(Order& order);
	void setOrderToPickUp(Order& order);
	void setOrderAsPaid(Order& order);
	void setComments(Order& order, string comment);
	bool validateOrder(Order order);
	SideOrder getSideOrder();
	Pizza getPizza();

	template<typename T>
	void validInput(const char& input, const vector<T>& vec) const;

private:
	int calculateCost(const Order& order);
	int calculateCost(const Pizza& pizza);
	int calculateOldCost(const Order& order);
	int calculateOldCost(const Pizza& pizza);
	void overrideOrder(int index, Order edit);
	void assignID(Order& order);
	vector<Offer> getSinglePizzaOffers();
	vector<Offer> getCompOffers();
	double orderSimularity(const Order& left, const Order& right);
	double pizzaSimularity(const Pizza& left, const Pizza& right);
};

template<typename T>
inline void SalesmanService::validInput(const char& input, const vector<T>& vec) const
{
	if (isalpha(input)) {
		throw InvalidInput("Input cannot be a character");
	}
	int numberEntered = (int)input - 49;
	if (numberEntered < 0) {
		throw InvalidInput("Input cannot be lower than 0");
	}
	if (numberEntered > vec.size()) {
		string msg = "Input cannot be bigger than " + to_string(vec.size());
		throw InvalidInput(msg);
	}
}
