#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "../pizza/Pizza.h"
using namespace std;

/*
	Keeps the user order, which can be multiple pizzas 
	and allows the user to edit his order.
*/
class Order
{
private:
	vector<Pizza> pizzas;
	double totalCost;
	void calculateCost();
public:
	Order();

	friend ostream& operator<< (ostream& out, const Order& order);
	void MakeOrder();
	void write(ofstream&  fout) const;
	void read(ifstream& fin);
	double getTotalCost();

private:
};
