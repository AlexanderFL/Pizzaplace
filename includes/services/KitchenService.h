#pragma once
#include "Data.h"
#include "Order.h"
#include "EmptyVector.h"

class KitchenService
{
private:
	Data repo;
public:
	KitchenService();
	void setOrderAsBaking(const int& index);
	void setOrderAsReady(const int& index);
	vector<Order> getOrders();
	vector<Order> getOrders(const Location& location);
};

