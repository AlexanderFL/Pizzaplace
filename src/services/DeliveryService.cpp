#include "DeliveryService.h"


DeliveryService::DeliveryService() {}

vector<Order> DeliveryService::getOrders() {
	vector<Order> orders;
	vector<Order> allorders = getItems<Order>();
	//TODO validate
	for (size_t i = 0; i < allorders.size(); i++) {
		if (allorders.at(i).getStatus() == READY) {
			orders.push_back(allorders.at(i));
		}
	}
	validateVectorNotEmpty(orders);
	return orders;
}

vector<Order> DeliveryService::getOrders(const Location& location) {
	vector<Order> orders;
	vector<Order> allorders = getItems<Order>();
	for (size_t i = 0; i < allorders.size(); i++) {
		if (allorders.at(i).getStatus() == READY && allorders.at(i).getLocation() == location) {
			orders.push_back(allorders.at(i));
		}
	}
	validateVectorNotEmpty(orders);
	return orders;
}

void DeliveryService::setOrderPaid(const size_t& id) {
	vector<Order> orders = repo.RetrieveAllFromFile<Order>();
	for (size_t i = 0; i < orders.size(); ++i) {
		if (orders.at(i).getID() == id) {
			orders.at(i).setOrderAsPaidFor(true);
			repo.WriteMultipleLinesToFile(orders);
			return;
		}
	}
}

void DeliveryService::setOrderDelivered(const size_t& id) {
	vector<Order> orders = repo.RetrieveAllFromFile<Order>();
	for (size_t i = 0; i < orders.size(); ++i) {
		if (orders.at(i).getID() == id) {
			orders.at(i).setStatus(SENT);
			repo.WriteMultipleLinesToFile(orders);
			return;
		}
	}
}