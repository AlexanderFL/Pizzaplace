#pragma once
#include <iostream>
#include "Pizza.h"
using namespace std;

class Order
{
public:
	Order();
	~Order();

	void AddOrder(Pizza pizza);
	void AddOrder();

protected:

private:
};
