#pragma once
#include "Data.h"
#include "Order.h"
#include "EmptyVector.h"
#include "InvalidString.h"

class KitchenService
{
private:
	Data repo;
public:
	KitchenService();
	void setOrderAsBaking(const size_t& id);
	void setOrderAsReady(const size_t& id);
	vector<Location> getLocations();
	vector<Order> getOrders();
	vector<Pizza> getPizzas(const Location& location);
	int convertStringToInt(const string& str) const;
private:
	template <class T> void validateVector(const vector<T>& vec) const;
	void validateString(const string& str) const;
};

template <class T> void KitchenService::validateVector(const vector<T>& vec) const {
	if (vec.size() == 0) {
		throw EmptyVector();
	}
}
