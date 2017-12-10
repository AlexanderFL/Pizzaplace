#pragma once

#include "Data.h"
#include "NumberInString.h"
#include "InvalidPrice.h"
#include "Offer.h"
#include "EmptyVector.h"
class ManagerService
{
private:
	Data repo;
public:
	ManagerService();
	void addTopping(Topping& topping);
	void addSideOrder(SideOrder& side);
	void addSpecialOrder(string ordername, const Order& order);
	void addDeliveryPlace(string place);
	void deleteTopping(int index);
	void deleteSideOrder(int index);
	void deleteLocation(int index);
	int getOrderTotalCost(const Order& order);
	vector<Topping> getToppings();
	void addLocation(Location& location);
	vector<Location> getLocations();

private:
	void containsOnlyAlpha(string s);
	void validPrice(int p);
	void assignID(Topping& toppging);
	void assignID(SideOrder& side);
	void assignID(Offer& offer);
	void assignID(Location& loc);
};

