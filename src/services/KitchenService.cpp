#include "KitchenService.h"


KitchenService::KitchenService() {}

void KitchenService::setOrderAsBaking(const size_t& id) {
	vector<Order> orders = getOrders();
	for (size_t i = 0; i < orders.size(); ++i) {
		for (size_t j = 0; j < orders.at(i).getPizzas().size(); ++j) {
			if (orders.at(i).getPizzas().at(j).getID() == id) {
				orders.at(i).getPizzas().at(j).setPhase(BAKING);
				repo.WriteMultipleLinesToFile(orders);
				return;
			}
		}
	}
}

void KitchenService::setOrderAsReady(const size_t& id) {
	vector<Order> orders = getOrders();
	for (size_t i = 0; i < orders.size(); ++i) {
		for (size_t j = 0; j < orders.at(i).getPizzas().size(); ++j) {
			if (orders.at(i).getPizzas().at(j).getID() == id) {
				orders.at(i).getPizzas().at(j).setPhase(READY);
				int counter = 0;
				for (size_t k = 0; k < orders.at(i).getPizzas().size(); ++k) {
					if (orders.at(i).getPizzas().at(k).getPhase() == READY) {
						++counter;
					}
				}
				if (orders.at(i).getPizzas().size() == counter) {
					orders.at(i).setStatus(READY);
				}
				repo.WriteMultipleLinesToFile(orders);
				return;
			}
		}
	}
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
		if (orders.at(i).getLocation() == location && orders.at(i).getStatus() == PREPERATION) {
			for (size_t j = 0; j < orders.at(i).getPizzas().size(); ++j) {
				if (orders.at(i).getPizzas().at(j).getPhase() == PREPERATION || orders.at(i).getPizzas().at(j).getPhase() == BAKING) {
					pizzas.push_back(orders.at(i).getPizzas().at(j));
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





