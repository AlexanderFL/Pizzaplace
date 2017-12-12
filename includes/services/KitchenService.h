#pragma once

#include "CommonService.h"
#include "Order.h"
#include "EmptyVector.h"
#include "InvalidString.h"

class KitchenService: public CommonService
{
private:
	Data repo;
public:
	KitchenService();
	void setOrderAsBaking(const size_t& id);
	void setOrderAsReady(const size_t& id);
	vector<Pizza> getPizzas(const Location& location);
	int convertStringToInt(const string& str) const;
private:
	void validateString(const string& str) const;
};