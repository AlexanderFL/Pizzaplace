#include "DeliveryService.h"


DeliveryService::DeliveryService() {}

vector<Location> DeliveryService::getLocations() {
	vector<Location> locations = repo.RetrieveAllFromFile<Location>();
	//TODO validate
	if (locations.size() == 0) {
		throw EmptyVector();
	}
	return locations;
}

vector<Order> DeliveryService::getOrders() {
	vector<Order> orders = repo.RetrieveAllFromFile<Order>();
	//TODO validate
	if (orders.size() == 0) {
		throw EmptyVector();
	}
	return orders;
}

vector<Order> DeliveryService::getOrders(const Location& location) {
	vector<Order> orders;
	vector<Order> allorders = getOrders();
	for (size_t i = 0; i < allorders.size(); i++) {
		if (allorders.at(i).getLocation() == location) {
			orders.push_back(orders.at(i));
		}
	}
	//TODO validate
	if (orders.size() == 0) {
		throw EmptyVector();
	}
	return orders;
}

void DeliveryService::setOrderPaid(const int& index) {
	vector<Order> orders = getOrders();
	//TODO validate
	orders.at(index).setOrderAsPaidFor(true);
	repo.WriteMultipleLinesToFile(orders);
}

void DeliveryService::setOrderDelivered(const int& index) {
	vector<Order> orders = getOrders();
	//TODO validate
	orders.at(index).setStatus(SENT);
	repo.WriteMultipleLinesToFile(orders);
}