#pragma once

#include "CommonService.h"
#include "NumberInString.h"
#include "InvalidPrice.h"
#include "Offer.h"
#include "EmptyVector.h"
#include "NumberInString.h"
#include "InvalidString.h"

class ManagerService: public CommonService
{
private:
	Data repo;
public:
	ManagerService();
	void addTopping(Topping& topping);
	void addSideOrder(SideOrder& side);
	void addCrust(PizzaCrust& crust);
	void addSpecialOrder(string ordername, const Order& order);
	void addDeliveryPlace(string place);
	int getOrderTotalCost(const Order& order);
	void addLocation(Location& location);
	//Order
	void addOffer(Offer& offer);
private:
	void containsOnlyAlpha(string s);
	void validPrice(int p);
	void validateString(const string& str);
};