#pragma once

#include <iostream>
#include <string>
#include "DeliveryService.h"
#include "CommonUI.h"
using namespace std;

class DeliveryUI : public CommonUI
{
private:
	DeliveryService service;
public:
	DeliveryUI();
	void deliveryMenu();
private:
	void allOrdersMenu();
	void ordersMenu();
	void orderMenu(int index, vector<Order> &orders, int loc);
};

