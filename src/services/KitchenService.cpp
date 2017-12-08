#include "KitchenService.h"


KitchenService::KitchenService() {}

void KitchenService::setOrderAsBaking(const int& index) {
	vector<Order> orders = getOrders();
	int counter = 0;
	for (size_t i = 0; i < tracker.size(); ++i) {
		for (size_t j = 0; j < tracker.at(i).size(); ++j) {
			if (tracker.at(i).at(j)) {
				if (counter++ == index) {
					orders.at(i).getPizzas().at(j).setPhase(BAKING);
					repo.WriteMultipleLinesToFile(orders);
					return;
				}
			}
		}
	}
}

void KitchenService::setOrderAsReady(const int& index) {
	vector<Order> orders = getOrders();
	int counter = 0;
	int readycounter = 0;
	for (size_t i = 0; i < tracker.size(); ++i) {
		for (size_t j = 0; j < tracker.at(i).size(); ++j) {
			if (tracker.at(i).at(j)) {
				if (counter++ == index) {
					orders.at(i).getPizzas().at(j).setPhase(READY);
					tracker.at(i).at(j) = false;
					++readycounter;
				}
			}
			else {
				++readycounter;
			}
		}
		if (readycounter == tracker.at(i).size() && orders.at(i).getStatus() == PREPERATION) {
			orders.at(i).setStatus(READY);
		}
	}
	repo.WriteMultipleLinesToFile(orders);
}

vector<Location> KitchenService::getLocations() {
	vector<Location> locations = repo.RetrieveAllFromFile<Location>();
	//validateVector(locations);
	if (locations.size() == 0) {
		throw EmptyVector();
	}
	return locations;
}

vector<Order> KitchenService::getOrders() {
	vector<Order> orders = repo.RetrieveAllFromFile<Order>();
	validateVector(orders);
	return orders;
}

vector<Pizza> KitchenService::getPizzas(const Location& location) {
	vector<Pizza> pizzas;
	vector<Order> orders = getOrders();
	for (size_t i = 0; i < orders.size(); ++i) {
		vector<bool> vec;
		tracker.push_back(vec);
		if (orders.at(i).getLocation() == location && orders.at(i).getStatus() == PREPERATION) {
			for (size_t j = 0; j < orders.at(i).getPizzas().size(); ++j) {
				if (orders.at(i).getPizzas().at(j).getPhase() == PREPERATION || orders.at(i).getPizzas().at(j).getPhase() == BAKING) {
					tracker.at(j).push_back(true);
					pizzas.push_back(orders.at(i).getPizzas().at(j));
				}
				else {
					tracker.at(j).push_back(false);
				}
			}
		}
	}
	//validateVector(pizzas);
	if (pizzas.size() == 0) {
		throw EmptyVector();
	}

	return pizzas;
}

void KitchenService::validateVector(const vector<Order>& vec) const {
	if (vec.size() == 0) {
		throw EmptyVector();
	}
}