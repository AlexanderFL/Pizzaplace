#include "MainUI.h"
/*
#include "Data.h"
#include "Offer.h"
#include <cmath>

#include <algorithm>
#include <vector>
struct target_less
{
	template<class It>
	bool operator()(It const &a, It const &b) const { return *a < *b; }
};
struct target_equal
{
	template<class It>
	bool operator()(It const &a, It const &b) const { return *a == *b; }
};
template<class It> It uniquify(It begin, It const end)
{
	std::vector<It> v;
	v.reserve(static_cast<size_t>(std::distance(begin, end)));
	for (It i = begin; i != end; ++i)
	{
		v.push_back(i);
	}
	std::sort(v.begin(), v.end(), target_less());
	v.erase(std::unique(v.begin(), v.end(), target_equal()), v.end());
	std::sort(v.begin(), v.end());
	size_t j = 0;
	for (It i = begin; i != end && j != v.size(); ++i)
	{
		if (i == v[j])
		{
			using std::iter_swap; iter_swap(i, begin);
			++j;
			++begin;
		}
	}
	return begin;
}

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
		total += pizza.getCrust().getPrice();
		total *= pizza.getPizzaSize().getPriceMod();
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
	/*vector<int> v1 = { 2,3,4,5,6,7,8,9,10 };
	vector<int> v2 = { 2,4,6,8,10 };
	vector<int> v3 = vector_diff(v1, v2);
		vector<int> v;
		v.push_back(6);
		v.push_back(5);
		v.push_back(5);
		v.push_back(8);
		v.push_back(5);
		v.push_back(8);
		v.erase(uniquify(v.begin(), v.end()), v.end());

	for (size_t i = 0; i < v.size(); ++i) {
		cout << v.at(i) << endl;
	}
	
	Order order;
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
	

	system("PAUSE");*/
	MainUI mainUI;
	mainUI.startUI();

	return 0;
}