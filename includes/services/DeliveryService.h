#pragma once

#include "CommonService.h"

class DeliveryService: public CommonService
{
private:
	Data repo;
public:
	DeliveryService();

	//Gets all orders that are in ready and need to be paid and delivered 
	vector<Order> getOrders();
	//Gets all orders that are in ready and need to be paid and delivered for a location
	vector<Order> getOrders(const Location& location);
	//Sets the order of the ID as paid
	void setOrderPaid(const size_t& id);
	//Sets the order of the ID as delivered
	void setOrderDelivered(const size_t& id);
};