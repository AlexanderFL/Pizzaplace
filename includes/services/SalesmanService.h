#pragma once
#include <iostream>
#include <string>
#include "Data.h"
#include "InvalidOrder.h"
#include "InvalidAddress.h"
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
	vector<Order> getAllOrders();
	vector<Location> getAllLocations();
	vector<SideOrder> getAllSideOrders();
	vector<Topping> getAllToppings();
	vector<PizzaCrust> getAllPizzaCrusts();
	vector<PizzaSize> getAllPizzaSizes();
private:
	int calculateCost(const Order& order);
	bool validateOrder(Order order);
	void overrideOrder(int index, Order edit);
	void assignID(Order& order);
};
