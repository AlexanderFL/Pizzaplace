#pragma once
#include <iostream>
#include <string>
#include "Data.h"
#include "InvalidOrder.h"
using namespace std;

class SalesmanService
{
private:
	Data _repo;
public:
	SalesmanService();

	void registerNewOrder(Order& order);
	void appendToOrder(Order& firstOrder, Order& secondOrder);
	int getPriceOfOrder(Order& order);
	void assignHomeAddress(Order& order, string address);
	void setOrderToDelivery(Order& order);
	void setOrderToPickUp(Order& order);
	void setOrderAsPaid(Order& order);
	void setComments(Order& order, string comment);
private:
	int calculateCost(const Order& order);
	bool validateOrder(Order order);
};
