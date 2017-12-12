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
	vector<SideOrder> getSides();
	//Order
	void addOffer(Offer& offer);
	vector<Offer> getOffers();
	void deletePizzaOnMenu(int index);
private:
	void containsOnlyAlpha(string s);
	void validPrice(int p);
};

