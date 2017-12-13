#pragma once

#include <iostream>
#include <string>
#include "DeliveryService.h"
#include "CommonUI.h"
using namespace std;

class DeliveryUI: public CommonUI
{
private:
	DeliveryService service;
public:
	DeliveryUI();
	void deliveryMenu();
	void allOrdersMenu();
	void ordersMenu();
	void showPizzaInfoShort(const Pizza& pizza) const;
	void showOrderInfo(const Order& order) const;
	void showOrderInfoShort(const Order& order) const;
};

