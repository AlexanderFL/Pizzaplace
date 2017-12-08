#include "DeliveryService.h"


DeliveryService::DeliveryService() {}

vector<Order> DeliveryService::getOrders() {
	vector<Order> orders = repo.RetrieveAllFromFile<Order>();
	//TODO validate
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