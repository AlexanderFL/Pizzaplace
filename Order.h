#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Pizza.h"
using namespace std;

/*
	Makes the user input the order
*/
class Order
{
private:
	vector<Pizza> pizzas;
	double totalCost;
public:
	Order();

	friend ostream& operator<< (ostream& out, const Order& order);
	void MakeOrder();

private:
};
