#pragma once

#include "CommonService.h"
#include "NumberInString.h"
#include "InvalidPrice.h"
#include "Offer.h"
#include "EmptyVector.h"
#include "NumberInString.h"
#include "InvalidString.h"
#include "InvalidInt.h"

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
	void addLocation(Location& location);
	int getOrderTotalCost(const Order& order);
	void replaceToppingInFile(const Topping& topping, int index);
	//Order
	void addOffer(Offer& offer);
	//Validation
	void containsOnlyAlpha(string s);
	void validPrice(int p);
private:
	void validateString(const string& str);
};