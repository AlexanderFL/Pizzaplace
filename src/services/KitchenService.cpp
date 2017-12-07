#include "KitchenService.h"


KitchenService::KitchenService() {}

void KitchenService::setOrderAsBaking(const int& index) {
	vector<Order> orders = getOrders();
	orders.at(index).setStatus(BAKING);
	repo.WriteMultipleLinesToFile(orders);
}

void KitchenService::setOrderAsReady(const int& index) {
	vector<Order> orders = getOrders();
	orders.at(index).setStatus(READY);
	repo.WriteMultipleLinesToFile(orders);
}

vector<Order> KitchenService::getOrders() {
	vector<Order> orders = repo.RetrieveAllFromFile<Order>();
	if (orders.size() == 0) {
		throw EmptyVector();
	}
	return orders;
}

vector<Order> KitchenService::getOrders(const Location& location) {
	vector<Order> orders;
	vector<Order> allorders = getOrders();
	for (size_t i = 0; i < allorders.size(); ++i) {
		if (allorders.at(i).getLocation() == location) {
			orders.push_back(allorders.at(i));
		}
	}
	if (orders.size() == 0) {
		throw EmptyVector();
	}
	return orders;
}