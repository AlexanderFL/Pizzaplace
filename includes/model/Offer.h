#pragma once
#include <iostream>
#include <string>

#include "Order.h"

using namespace std;

class Offer
{
private:
	string _offername;
	Order _order;
public:
	Offer(string offername, Order order);

	string getOffername();
	Order getOrder();
};
