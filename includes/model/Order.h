#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Pizza.h"
#include "SideOrder.h"
#include "Location.h"
using namespace std;

/*
	Keeps the user order, which can be multiple pizzas 
	and allows the user to edit his order.
*/

class Order
{
public:
	static const string filename;
private:
	vector<Pizza> pizzas;
	vector<SideOrder> sides;
	double totalCost;
	int status;
	Location location;
	string comment;
	string homeAddress;

	void calculateCost();

public:
	Order();
	Order(vector<Pizza> pizzas, vector<SideOrder> sides, double totalCost, int status, Location location, string comment, string homeAddress);
	friend ostream& operator << (ostream& out, const Order& order);
	friend istream& operator >> (istream& in, Order& order);
	friend bool operator == (const Order& left, const Order& right);
	friend bool operator != (const Order& left, const Order& right);
	friend bool operator <= (const Order& left, const Order& right);
	friend Order operator * (const Order& left, const Order& right);
	void MakeOrder();
	double getTotalCost();

	//TODO: Fix homeaddress
	void setHomeAddress(string address);

	int getPizzaOrderLength() const;
	int getSideOrderLength() const;
	Pizza getPizzaIndex(int index) const;
	SideOrder getSideOrderIndex(int index) const;
	string getHomeAddress() const;
};
