#pragma once

#include "Data.h"
#include "NumberInString.h"
#include "InvalidPrice.h"
#include "Offer.h"
#include "EmptyVector.h"
#include "NumberInString.h"
#include "InvalidString.h"

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
	int getOrderTotalCost(const Order& order);
	void addLocation(Location& location);
	//Order
	void addOffer(Offer& offer);
	template<class T> vector<T> getAll();
	template<class T> void addItem(T item);
	template<class T> void deleteItem(int index);
private:
	void containsOnlyAlpha(string s);
	void validPrice(int p);
	void validateString(const string& str);
	template<class T> void validateVectorNotEmpty(const vector<T>& items);
};

template<class T> vector<T> ManagerService::getAll() {
	vector<T> items = repo.RetrieveAllFromFile<T>();
	validateVectorNotEmpty(items);
	return items;
}

template<class T> void ManagerService::addItem(T item) {
	repo.WriteToFile(item);
}

template<class T> void ManagerService::deleteItem(int index) {
	repo.RemoveFromFileAtIndex<T>(index);
}

template<class T> void ManagerService::validateVectorNotEmpty(const vector<T>& items) {
	if (items.size() == 0) {
		throw EmptyVector();
	}
}