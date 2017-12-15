#pragma once

#include "DeliveryService.h"
#include "CommonUI.h"

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

