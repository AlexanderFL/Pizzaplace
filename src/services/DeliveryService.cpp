#include "DeliveryService.h"


DeliveryService::DeliveryService() {}

vector<Location> DeliveryService::getLocations() {
	vector<Location> locations = repo.RetrieveAllFromFile<Location>();
	//TODO validate
	validateVector(locations);
	return locations;
}

vector<Order> DeliveryService::getOrders() {
	vector<Order> orders;
	vector<Order> allorders = repo.RetrieveAllFromFile<Order>();
	//TODO validate
	for (size_t i = 0; i < allorders.size(); i++) {
		if (allorders.at(i).getStatus() == READY) {
			orders.push_back(orders.at(i));
		}
	}
	validateVector(orders);
	return orders;
}

vector<Order> DeliveryService::getOrders(const Location& location) {
	vector<Order> orders;
	vector<Order> allorders = getOrders();
	for (size_t i = 0; i < allorders.size(); i++) {
		if (allorders.at(i).getStatus() == READY && allorders.at(i).getLocation() == location) {
			orders.push_back(orders.at(i));
		}
	}
	//TODO validate
	validateVector(orders);
	return orders;
}

void DeliveryService::setOrderPaid(const size_t& id) {
	vector<Order> orders = getOrders();
	//TODO validate
	for (size_t i = 0; i < orders.size(); ++i) {
		if (orders.at(i).getID() == id) {
			orders.at(i).setOrderAsPaidFor(true);
			repo.WriteMultipleLinesToFile(orders);
			return;
		}
	}
}

void DeliveryService::setOrderDelivered(const size_t& id) {
	vector<Order> orders = getOrders();
	//TODO validate
	for (size_t i = 0; i < orders.size(); ++i) {
		if (orders.at(i).getID() == id) {
			orders.at(i).setStatus(SENT);
			repo.WriteMultipleLinesToFile(orders);
			return;
		}
	}
}

int DeliveryService::convertStringToInt(const string& str) const {
	validateString(str);
	return stoi(str);
}

void DeliveryService::validateString(const string& str) const {
	if (str.length() == 0) {
		throw InvalidString();
	}
	for (size_t i = 0; i < str.length(); ++i) {
		if (!isdigit(str[i])) {
			throw InvalidString();
		}
	}
}