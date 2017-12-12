#pragma once

#include "CommonService.h"
#include "EmptyVector.h"
#include "InvalidString.h"

class DeliveryService: public CommonService
{
private:
	Data repo;
public:
	DeliveryService();

	vector<Order> getOrders();
	vector<Order> getOrders(const Location& location);
	void setOrderPaid(const size_t& id);
	void setOrderDelivered(const size_t& id);
	int convertStringToInt(const string& str) const;
private:
	void validateString(const string& str) const;
};