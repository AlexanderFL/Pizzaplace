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
	void addCrust(PizzaCrust& crust);
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
	void addSize(PizzaSize& size);
	void deleteSize(int index);
	template<class T> vector<T> getAll();
	template<class T> void addItem(T item);
	template<class T> void deleteItem(int index);
private:
	void containsOnlyAlpha(string s);
	void validPrice(int p);
};

template<class T> vector<T> ManagerService::getAll() {
	return repo.RetrieveAllFromFile<T>();
}

template<class T> void ManagerService::addItem(T item) {
	repo.WriteToFile(item);
}

template<class T> void ManagerService::deleteItem(int index) {
	repo.RemoveFromFileAtIndex<T>(index);
}