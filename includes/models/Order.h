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

enum deliveryMethod { PICKUP = 0, SEND };
enum status { PREPERATION = 0, BAKING, READY, SENT};

class Order
{
public:
	static const string filename;
private:
	vector<Pizza> pizzas;
	vector<SideOrder> sides;
	string comment;
	string homeAddress;
	Location location;
	status _status;
	deliveryMethod _deliveryMethod;
	double totalCost;
	bool paidFor;

public:
	Order();
	Order(vector<Pizza> pizzas, vector<SideOrder> sides, status orderStatus, Location location, string comment, string homeAddress, deliveryMethod orderDeliveryMethod, bool isPaid);
	friend ostream& operator << (ostream& out, const Order& order);
	friend istream& operator >> (istream& in, Order& order);
	friend bool operator == (const Order& left, const Order& right);
	friend bool operator != (const Order& left, const Order& right);
	friend bool operator <= (const Order& left, const Order& right);
	friend Order operator * (const Order& left, const Order& right);

	vector<Pizza> getPizzas() const;
	vector<SideOrder> getSides() const;
	status getStatus() const;
	Location getLocation() const;
	string getComment() const;
	string getHomeAddress() const;
	deliveryMethod getDeliveryMethod() const;
	bool isPaidFor() const;

	void setPizzas(const vector<Pizza>& pizzas);
	void setSides(const vector<SideOrder>& sides);
	void setStatus(const status& orderStatus);
	void setLocation(const Location& location);
	void setComment(const string& comment);
	void setHomeAddress(const string& homeAddress);
	void setDeliveryMethod(const deliveryMethod& orderDeliveryMethod);
	void setOrderAsPaidFor(bool isPaid);
};
