#pragma once
#include "Data.h"
#include "EmptyVector.h"
#include "InvalidString.h"

class DeliveryService
{
private:
	Data repo;
public:
	DeliveryService();

	vector<Location> getLocations();
	vector<Order> getOrders();
	vector<Order> getOrders(const Location& location);
	void setOrderPaid(const size_t& id);
	void setOrderDelivered(const size_t& id);
	int convertStringToInt(const string& str) const;
private:
	template <class T> void validateVector(const vector<T>& vec) const;
	void validateString(const string& str) const;
};

template <class T> void DeliveryService::validateVector(const vector<T>& vec) const {
	if (vec.size() == 0) {
		throw EmptyVector();
	}
}
