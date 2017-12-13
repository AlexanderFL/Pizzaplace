#include "MainUI.h"

#include "Data.h"
#include "Offer.h"
#include <cmath>

#include <vector>


vector<Offer> getPizzaOffers() {
	Data repo;
	vector<Offer> offers;
	vector<Offer> alloffers = repo.RetrieveAllFromFile<Offer>();
	for (size_t i = 0; i < alloffers.size(); ++i) {
		if (alloffers.at(i).getOrder().getPizzas().size() == 1 && alloffers.at(i).getOrder().getSides().size() == 0) {
			offers.push_back(alloffers.at(i));
		}
	}
	return offers;
}

vector<Offer> getCompOffers() {
	Data repo;
	vector<Offer> offers;
	vector<Offer> alloffers = repo.RetrieveAllFromFile<Offer>();
	for (size_t i = 0; i < alloffers.size(); ++i) {
		if (!(alloffers.at(i).getOrder().getPizzas().size() == 1 && alloffers.at(i).getOrder().getSides().size() == 0)) {
			offers.push_back(alloffers.at(i));
		}
	}
	return offers;
}

string getMostSimilarName(const vector<Offer>& offers, const Pizza& pizza) {
	string str = "";
	int index = -1;
	double sim = 0;
	for (size_t i = 0; i < offers.size(); ++i) {
		Pizza comp = offers.at(i).getOrder().getPizzas().at(0) * pizza;
		if (comp.getToppings().size() >= offers.at(i).getOrder().getPizzas().at(0).getToppings().size()) {
			double temp = (offers.at(i).getOrder().getPizzas().at(0) * pizza).getToppings().size() / (sqrt(offers.at(i).getOrder().getPizzas().at(0).getToppings().size()) * sqrt(pizza.getToppings().size()));
			if (sim < temp) {
				sim = temp;
				index = i;
			}
		}
	}
	if (index == -1) {
		return "Custom Pizza";
	}
	else {
		if (pizza == offers.at(index).getOrder().getPizzas().at(0)) {
			return offers.at(index).getName();
		}
		else {
			return offers.at(index).getName() + "+";
		}
	}
}

int getMostSimilarPrice(const vector<Offer>& offers, const Pizza& pizza) {
	int total = 0;
	int index = -1;
	double sim = 0;
	for (size_t i = 0; i < offers.size(); ++i) {
		Pizza comp = offers.at(i).getOrder().getPizzas().at(0) * pizza;
		if (comp.getToppings().size() >= offers.at(i).getOrder().getPizzas().at(0).getToppings().size()) {
			double temp = (offers.at(i).getOrder().getPizzas().at(0) * pizza).getToppings().size() / (sqrt(offers.at(i).getOrder().getPizzas().at(0).getToppings().size()) * sqrt(pizza.getToppings().size()));
			if (sim < temp) {
				sim = temp;
				index = i;
			}
		}
	}
	if (index == -1) {
		//normal
		for (size_t i = 0; i < pizza.getToppings().size(); ++i) {
			total += pizza.getToppings().at(i).getPrice();
		}
		//total += pizza.getCrust().getPrice();
		//total *= pizza.getPizzaSize().getPriceMod();
	}
	else {
		total += offers.at(index).getPrice();
		if (pizza != offers.at(index).getOrder().getPizzas().at(0)) {
			Pizza temp = pizza - offers.at(index).getOrder().getPizzas().at(0);
			for (size_t i = 0; i < temp.getToppings().size(); ++i) {
				total += temp.getToppings().at(i).getPrice();
			}
		}
	}
	return total;
}

double sim(const Order& left, const Order& right) {

	return ((left * right).getPizzas().size() + (left * right).getSides().size()) / ((sqrt(left.getPizzas().size()) * sqrt(right.getPizzas().size())) + (sqrt(left.getSides().size()) * sqrt(right.getSides().size())));
}

int calcPrice(const Order& order) {
	int total = 0;
	vector<Pizza> pizzas = order.getPizzas();
	vector<SideOrder> sides = order.getSides();
	vector<Offer> offers = getPizzaOffers();

	for (size_t i = 0; i < sides.size(); ++i) {
		total += sides.at(i).getPrice();
	}
	return total;
}

void detectOffers(const Order& order) {
	vector<Offer> singles = getPizzaOffers();
	vector<Offer> comps = getCompOffers();
	vector<Offer> tempExt;
	vector<Offer> ext;
	Order temp = order;
	while (comps.size() > 0) {
		if (comps.at(0).getOrder() == order) {
			cout << comps.at(0).getName() << " " << comps.at(0).getPrice() << endl;
			return;
		}
		else if (comps.at(0).getOrder() <= order) {
			tempExt.push_back(comps.at(0));
		}
		comps.erase(comps.begin());
	}
	while (tempExt.size() > 0) {
		bool unique = true;
		for (size_t i = 1; i < tempExt.size(); ++i) {
			if (sim(tempExt.at(0).getOrder(), tempExt.at(i).getOrder()) != 0) {
				if (sim(tempExt.at(0).getOrder(), order) < sim(tempExt.at(i).getOrder(), order)) {
					tempExt.erase(tempExt.begin());
				}
				else {
					tempExt.erase(tempExt.begin() + i);
				}
				unique = false;
				break;
			}
		}
		if (unique) {
			ext.push_back(tempExt.at(0));
			tempExt.erase(tempExt.begin());
		}
	}
	for (size_t i = 0; i < ext.size(); ++i) {
		cout << ext.at(i).getName() << " " << ext.at(i).getPrice() << endl;
		temp = temp - ext.at(i).getOrder();
	}
	for (size_t i = 0; i < temp.getPizzas().size(); ++i) {
		cout << getMostSimilarName(singles, temp.getPizzas().at(i)) << " " << getMostSimilarPrice(singles, temp.getPizzas().at(i)) << endl;
	}
	for (size_t i = 0; i < temp.getSides().size(); ++i) {

	}
}

int main() {
	/*Order order;
	vector<Pizza> pizzas;
	Pizza pizza;
	pizza.addToppings(Topping("Spinach", 32));
	pizza.addToppings(Topping("Kale", 43));
	Pizza pizza2;
	pizza2.addToppings(Topping("Pineapple", 50));
	pizza2.addToppings(Topping("Pineapple", 50));
	Pizza pizza3;
	pizza3.addToppings(Topping("Spinach", 32));
	pizza3.addToppings(Topping("Kale", 43));
	pizza3.addToppings(Topping("Pineapple", 50));
	pizzas.push_back(pizza);
	pizzas.push_back(pizza2);
	pizzas.push_back(pizza3);
	order.setPizzas(pizzas);
	
	vector<Offer> offers = getPizzaOffers();
	/*for (size_t i = 0; i < order.getPizzas().size(); ++i) {
		cout << getMostSimilarName(offers, order.getPizzas().at(i)) << endl;
	}
	for (size_t i = 0; i < order.getPizzas().size(); ++i) {
		cout << getMostSimilarPrice(offers, order.getPizzas().at(i)) << endl;
	}*/
	//detectOffers(order);

	//system("PAUSE");
	MainUI mainUI;
	mainUI.startUI();

	return 0;
}