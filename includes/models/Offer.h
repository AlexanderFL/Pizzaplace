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
	Offer();
	Offer(string name, Order order, int price, bool fixed);

	string getOffername();
	Order getOrder();

	friend ostream& operator << (ostream& out, const Offer& offer);
	friend istream& operator >> (istream& in, Offer& offer);
};
