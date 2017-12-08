#pragma once
#include "Data.h"
#include "EmptyVector.h"

class DeliveryService
{
private:
	Data repo;
public:
	DeliveryService();

	vector<Location> getLocations();
	vector<Order> getOrders();
	vector<Order> getOrders(const Location& location);
	void setOrderPaid(const int& index);
	void setOrderDelivered(const int& index);
};

