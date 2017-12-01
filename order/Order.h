#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "../pizza/Pizza.h"
#include "SideOrder.h"
using namespace std;

/*
	Keeps the user order, which can be multiple pizzas 
	and allows the user to edit his order.
*/

class Order
{
private:
	vector<Pizza> pizzas;
	vector<SideOrder> sides;
	double totalCost;
	int status;
	int location;
	string comment;
	void calculateCost();
	string homeAddress;

public:
	Order();
	friend ostream& operator << (ostream& out, const Order& order);
	friend bool operator == (const Order& left, const Order& right);
	void MakeOrder();
	void write(ofstream&  fout) const;
	void read(ifstream& fin);
	double getTotalCost();
	//TODO: Fix homeaddress
	void setHomeAddress(string address);
	string getHomeAddress();
};
