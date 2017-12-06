#pragma once

#include "Data.h"
#include "NumberInString.h";
#include "InvalidPrice.h";

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

	vector<Topping> getToppings();
};

