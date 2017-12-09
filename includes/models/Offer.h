#pragma once
#include <iostream>
#include <string>

#include "Order.h"

using namespace std;

class Offer
{
public:
	static const string filename;
private:
	string name;
	Order order;
	int price;
	bool fixed;
public:
	// Constructors
	Offer();
	Offer(string name, Order order, int price, bool fixed);

	// Get functions
	string getName() const;
	Order getOrder() const;
	int getPrice() const;
	bool getFixed() const;

	// Set functions
	void setName(const string& name);
	void setOrder(const Order& order);
	void setPrice(const int& price);
	void setFixed(const bool& fixed);

	// Operator overloads
	friend ostream& operator << (ostream& out, const Offer& offer);
	friend istream& operator >> (istream& in, Offer& offer);
};
