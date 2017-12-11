#pragma once
#include <iostream>
#include <string>
#include "DeliveryService.h"
#include "EmptyVector.h"
using namespace std;

class DeliveryUI
{
private:
	DeliveryService service;
	bool ignore;
public:
	DeliveryUI();
	void setIgnore(bool ignore);
	void deliveryMenu();
	void allOrdersMenu();
	void ordersMenu();
};

