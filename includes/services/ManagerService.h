#pragma once

#include "Data.h"
#include "NumberInString.h"
#include "InvalidPrice.h"
#include "Offer.h"

class ManagerService
{
private:
	Data repo;
public:
	ManagerService();
	void addTopping(const Topping& topping);
	void addSideOrder(const SideOrder& side);
	void addSpecialOrder(string ordername, const Order& order);
	void addDeliveryPlace(string place);
	void deleteTopping(int index);
	int getOrderTotalCost(const Order& order);
	vector<Topping> getToppings();
private:
	bool containsOnlyAlpha(string s);
	bool validPrice(double p);
};

