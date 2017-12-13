#include "MainUI.h"

/*#include "Data.h"
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

vector<int> vector_diff(vector<int> model, vector<int> pattern) {
	vector<int> mod = model;
	vector<int> pat = pattern;
	vector<int> temp;
	int found = 0;

	for (int i = 0; i < mod.size(); i++) {
		for (int k = 0; k < pat.size(); k++) {
			if (mod[i] == pat[k]) {
				found = 0; // add this
				break;
			}
			else if (mod[i] != pat[k]) {
				found = mod[i];
			}
		}
		if (found != 0) { // to trigger this and not save garbage
			temp.push_back(found);
		}
	}
	return temp;
}*/

int main() {
	/*Order order;
	vector<Pizza> pizzas;
	Pizza pizza;
	pizza.addToppings(Topping("Spinach", 32));
	pizzas.push_back(pizza);
	pizza.addToppings(Topping("Spinach", 32));
	pizza.addToppings(Topping("Kale", 43));
	pizza.addToppings(Topping("Kale", 43));
	pizzas.push_back(pizza);
	order.setPizzas(pizzas);
	
	vector<Offer> offers = getPizzaOffers();
	for (size_t i = 0; i < order.getPizzas().size(); ++i) {
		cout << getMostSimilarName(offers, order.getPizzas().at(i)) << endl;
	}
	for (size_t i = 0; i < order.getPizzas().size(); ++i) {
		cout << getMostSimilarPrice(offers, order.getPizzas().at(i)) << endl;
	}
	

	system("PAUSE");*/
	MainUI mainUI;
	mainUI.startUI();

	return 0;
}