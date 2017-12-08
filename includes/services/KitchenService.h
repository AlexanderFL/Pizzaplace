#pragma once
#include "Data.h"
#include "Order.h"
#include "EmptyVector.h"

class KitchenService
{
private:
	Data repo;
	vector<vector<bool>> tracker;
public:
	KitchenService();
	void setOrderAsBaking(const int& index);
	void setOrderAsReady(const int& index);
	vector<Location> getLocations();
	vector<Order> getOrders();
	vector<Pizza> getPizzas(const Location& location);
private:
	void validateVector(const vector<Order>& vec) const;
};

