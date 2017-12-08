#include "DeliveryService.h"


DeliveryService::DeliveryService() {}

vector<Order> getOrders() {
	vector<Order> orders = repo.ReadAllFromFile<Order>();
	//TODO validate
	return orders;
}

vector<Order> getOrders(const Location& location) {
	vector<Order> orders;
	vector<Order> allorders = getOrders();
	for (size_t i = 0; i < allorders.size(); i++) {
		if (allorders.at(i).getLocation() == location) {
			orders.push_back(orders);
		}
	}
	//TODO validate
	return orders;
}

void setOrderPaid(const int& index) {

}

void setOrderDelivered(const int& index) {

}