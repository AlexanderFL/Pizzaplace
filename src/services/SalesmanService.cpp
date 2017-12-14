#include "SalesmanService.h"


SalesmanService::SalesmanService(){
	_repo = Data();
}

void SalesmanService::registerNewOrder(Order& order){
	if (validateOrder(order)) {
		assignID(order);
		_repo.WriteToFile(order);
	}
	else {
		throw InvalidOrder();
	}
}

void SalesmanService::appendToOrder(Order& firstOrder, Order& secondOrder){
	//validate
	if (validateOrder(firstOrder) && validateOrder(secondOrder)) {
		//grab all orders from file
		vector<Order> orders = _repo.RetrieveAllFromFile<Order>();
		for (int i = 0; i < orders.size(); i++) {
			//find the order to append to
			if (orders[i] == firstOrder) { 
				//append the second order to first
				firstOrder = firstOrder + secondOrder;
				//override in file
				overrideOrder(i, firstOrder);
				break;
			}
		}
	}
	else {
		throw InvalidOrder();
	}
}

// Appends a pizza to a order
void SalesmanService::appendToOrder(Order& firstOrder, Pizza &pizza){
	// Get the pizzas from a order
	vector<Pizza> pizzaVector = firstOrder.getPizzas();
	// Append the pizza given in parameter
	pizzaVector.push_back(pizza);
	// Set the vector back in order
	firstOrder.setPizzas(pizzaVector);
}

// Appends sides to a order
void SalesmanService::appendToOrder(Order& order, SideOrder &sideAppend){
	vector<SideOrder> sidesVector = order.getSides();
	sidesVector.push_back(sideAppend);
	order.setSides(sidesVector);
}

Pizza SalesmanService::getPizza(){
	return _pizza;
}

int SalesmanService::getPriceOfOrder(Order& order){
	int price = calculateCost(order);
	return price;
}

int SalesmanService::getOldPriceOfOrder(Order& order){
	int price = calculateOldCost(order);
	return price;
}

void SalesmanService::assignHomeAddress(Order& order, string address){
	//address must contain at least one character and one number
	//ex. of address: 'Menntavegur 1' or 'Skogarstigur 12'
	//
	//address can be empty if deliverymethod is pickup
	bool containsCharacter = false;
	bool containsNumber = false;
	if (address == "" && order.getDeliveryMethod() == PICKUP) {
		order.setHomeAddress(address);
	}
	else{
		for (int i = 0; i < address.length(); i++) {
			if (isalpha(address[i]) && !containsCharacter) {
				containsCharacter = true;
			}
			if (isalnum(address[i]) && !containsNumber) {
				containsNumber = true;
			}
		}
		if (containsCharacter && containsNumber) {
			order.setHomeAddress(address);
		}
		else {
			throw InvalidAddress();
		}
	}
}

/*			Validate the Order			*/
bool SalesmanService::validateOrder(Order order) {
	// Just check if both pizzas and sides vectors are emtpy
	if (order.getPizzas().empty() && order.getSides().empty()) {
		return false;
	}
	return true;
}

void SalesmanService::validInput(const char& input, const int& max, const int& min) const{
	if (isalpha(input)) {
		throw InvalidInput("Input cannot be a character");
	}
	int numberEntered = (int)input - 48;
	if (numberEntered < min) {
		const std::string& msg = "Input cannot be lower than " + to_string(min);
		throw InvalidInput(msg);
	}
	if (numberEntered > max) {
		const std::string& msg = "Input cannot be bigger than " + to_string(max);
		throw InvalidInput(msg);
	}
}

void SalesmanService::setOrderToDelivery(Order& order) {
	order.setDeliveryMethod(SEND);
}

void SalesmanService::setOrderToPickUp(Order& order) {
	order.setDeliveryMethod(PICKUP);
}

void SalesmanService::setOrderAsPaid(Order& order){
	order.setOrderAsPaidFor(true);
}

void SalesmanService::setComments(Order& order, string comment){
	order.setComment(comment);
}

SideOrder SalesmanService::getSideOrder(){
	return _sides;
}

vector<string> SalesmanService::getOfferNames(const Order& order) {
	vector<string> offernames;
	vector<Offer> comps = getCompOffers();
	vector<Offer> extras;
	Order temp = order;
	while (comps.size() > 0) {
		if (comps.at(0).getOrder() == order) {
			offernames.push_back(comps.at(0).getName());
			return offernames;
		}
		else if (comps.at(0).getOrder() <= order) {
			extras.push_back(comps.at(0));
		}
		comps.erase(comps.begin());
	}
	while (extras.size() > 0) {
		bool unique = true;
		for (size_t i = 1; i < extras.size(); ++i) {
			if (orderSimularity(extras.at(0).getOrder(), extras.at(i).getOrder()) != 0) {
				if (orderSimularity(extras.at(0).getOrder(), order) < orderSimularity(extras.at(i).getOrder(), order)) {
					extras.erase(extras.begin());
				}
				else {
					extras.erase(extras.begin() + i);
				}
				unique = false;
				break;
			}
		}
		if (unique) {
			offernames.push_back(extras.at(0).getName());
			temp = temp - extras.at(0).getOrder();
			extras.erase(extras.begin());
		}
	}
	for (size_t i = 0; i < temp.getPizzas().size(); ++i) {
		offernames.push_back(getSingleOfferName(temp.getPizzas().at(i)));
	}
	return offernames;
}

string SalesmanService::getSingleOfferName(const Pizza& pizza) {
	vector<Offer> singles = getSinglePizzaOffers();
	int index = -1;
	double sim = 0;
	for (size_t i = 0; i < singles.size(); ++i) {
		Pizza comp = singles.at(i).getOrder().getPizzas().at(0) * pizza;
		if (comp.getToppings().size() >= singles.at(i).getOrder().getPizzas().at(0).getToppings().size()) {
			double temp = pizzaSimularity(singles.at(i).getOrder().getPizzas().at(0), pizza);
			if (sim < temp) {
				sim = temp;
				index = i;
			}
		}
	}
	if (index != -1) {
		Pizza extras = pizza - singles.at(index).getOrder().getPizzas().at(0);
		Pizza specials = pizza - extras;
		if (!extras.getToppings().empty()) {
			return singles.at(index).getName() + "+";
		}
		else {
			return singles.at(index).getName();
		}
	}
	else {
		return "Custom Pizza";
	}
}

/*

	PRIVATE FUNCTIONS

*/

int SalesmanService::calculateCost(const Order& order) {
	int total = 0;
	vector<Offer> comps = getCompOffers();
	vector<Offer> tempExt;
	vector<Offer> ext;
	Order temp = order;
	while (comps.size() > 0) {
		if (comps.at(0).getOrder() == order) {
			for (size_t i = 0; i < order.getPizzas().size(); ++i) {
				total += calculateSimpleCost(order.getPizzas().at(i));
			}
			for (size_t i = 0; i < order.getSides().size(); ++i) {
				total += order.getSides().at(i).getPrice();
			}
			total *= (comps.at(0).getPrice() / 100.0);
			return total * (comps.at(0).getPrice() / 100.0);
		}
		else if (comps.at(0).getOrder() <= order) {
			tempExt.push_back(comps.at(0));
		}
		comps.erase(comps.begin());
	}
	while (tempExt.size() > 0) {
		bool unique = true;
		for (size_t i = 1; i < tempExt.size(); ++i) {
			if (orderSimularity(tempExt.at(0).getOrder(), tempExt.at(i).getOrder()) != 0) {
				if (orderSimularity(tempExt.at(0).getOrder(), order) < orderSimularity(tempExt.at(i).getOrder(), order)) {
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
			int exttotal = 0;
			for (size_t i = 0; i < tempExt.at(0).getOrder().getPizzas().size(); ++i) {
				exttotal += calculateSimpleCost(tempExt.at(0).getOrder().getPizzas().at(i));
			}
			for (size_t i = 0; i < tempExt.at(0).getOrder().getSides().size(); ++i) {
				exttotal += tempExt.at(0).getOrder().getSides().at(i).getPrice();
			}
			total += exttotal * (tempExt.at(0).getPrice() / 100.0);
			temp = temp - tempExt.at(0).getOrder();
			tempExt.erase(tempExt.begin());
		}
	}
	for (size_t i = 0; i < temp.getPizzas().size(); ++i) {
		total += calculateCost(temp.getPizzas().at(i));
	}
	for (size_t i = 0; i < temp.getSides().size(); ++i) {
		total += temp.getSides().at(i).getPrice();
	}
	return total;
}

int SalesmanService::calculateCost(const Pizza& pizza) {
	int total = 0;
	vector<Offer> singles = getSinglePizzaOffers();
	int index = -1;
	double sim = 0;
	for (size_t i = 0; i < singles.size(); ++i) {
		Pizza comp = singles.at(i).getOrder().getPizzas().at(0) * pizza;
		if (comp.getToppings().size() >= singles.at(i).getOrder().getPizzas().at(0).getToppings().size()) {
			double temp = pizzaSimularity(singles.at(i).getOrder().getPizzas().at(0), pizza);
			if (sim < temp) {
				sim = temp;
				index = i;
			}
		}
	}
	if (index == -1) {
		//normal
		return calculateSimpleCost(pizza);
	}
	else {
		Pizza extras = pizza - singles.at(index).getOrder().getPizzas().at(0);
		Pizza specials = pizza - extras;
		total += calculateSimpleCost(pizza);
		total *= (singles.at(index).getPrice() / 100.0);
		for (size_t i = 0; i < extras.getToppings().size(); ++i) {
			total += extras.getToppings().at(i).getPrice();
		}
		return total;
	}
}

vector<Offer> SalesmanService::getSinglePizzaOffers() {
	vector<Offer> offers;
	vector<Offer> alloffers = getItems<Offer>();
	for (size_t i = 0; i < alloffers.size(); ++i) {
		if (alloffers.at(i).getOrder().getPizzas().size() == 1 && alloffers.at(i).getOrder().getSides().size() == 0) {
			offers.push_back(alloffers.at(i));
		}
	}
	return offers;
}

vector<Offer> SalesmanService::getCompOffers() {
	vector<Offer> offers;
	vector<Offer> alloffers = getItems<Offer>();
	for (size_t i = 0; i < alloffers.size(); ++i) {
		if (!(alloffers.at(i).getOrder().getPizzas().size() == 1 && alloffers.at(i).getOrder().getSides().size() == 0)) {
			offers.push_back(alloffers.at(i));
		}
	}
	return offers;
}

double SalesmanService::orderSimularity(const Order& left, const Order& right) {
	double top = ((left * right).getPizzas().size() + (left * right).getSides().size());
	double bottom = ((sqrt(left.getPizzas().size()) * sqrt(right.getPizzas().size())) + (sqrt(left.getSides().size()) * sqrt(right.getSides().size())));
	return top / bottom;
}

double SalesmanService::pizzaSimularity(const Pizza& left, const Pizza& right) {
	double top = (left * right).getToppings().size();
	double bottom = (sqrt(left.getToppings().size()) * sqrt(right.getToppings().size()));
	return  top / bottom;
}

/*			Returns total cost for the order		*/
int SalesmanService::calculateOldCost(const Order& order) {
	int total = 0;
	size_t numberOfPizzas = order.getPizzas().size();
	// Pizza cost
	for (size_t i = 0; i < numberOfPizzas; ++i) {
		total += calculateOldCost(order.getPizzas().at(i));
	}
	// Side orders cost
	for (int i = 0; i < order.getSides().size(); ++i) {
		total += order.getSides().at(i).getPrice();

	}
	return total;
}

/*			Returns total cost for the pizza		*/
int SalesmanService::calculateSimpleCost(const Pizza& pizza) {
	int total = 0;
	size_t numberOfToppingsOnPizza = pizza.getToppings().size();
	// Add each topping to the price price
	for (size_t j = 0; j < numberOfToppingsOnPizza; ++j) {
		total += pizza.getToppings().at(j).getPrice(); 
	}
	//Add each crust to the price
	total += pizza.getCrust().getPrice(); 
	// Multiply the pizza size mod to the price
	total *= pizza.getPizzaSize().getPriceMod(); 
	return total;
}

int SalesmanService::calculateOldCost(const Pizza& pizza) {
	int total = 0;
	size_t numberOfToppingsOnPizza = pizza.getToppings().size();
	// Add each topping to the price
	for (size_t j = 0; j < numberOfToppingsOnPizza; ++j) {
		total += pizza.getToppings().at(j).getPrice();
	}
	// Add type of crust to the price
	total += pizza.getCrust().getPrice(); 
	// Multiply the pizza size mod to the price
	total *= pizza.getPizzaSize().getPriceMod(); 
	return total;
}

void SalesmanService::overrideOrder(int index, Order edit) {
	_repo.ModifyFileAtIndex<Order>(index, edit);
}

void SalesmanService::assignID(Order& order) {
	try {
		vector<Order> orders = getItems<Order>();
		size_t id = 1;
		if (orders.size() == 0) {
			order.setID(1);
		}
		else {
			order.setID(orders.at(orders.size() - 1).getID() + 1);
			for (size_t i = orders.size(); i > 0; --i) {
				if (orders.at(i - 1).getPizzas().size() > 0) {
					id = orders.at(i - 1).getPizzas().at(orders.at(i - 1).getPizzas().size() - 1).getID() + 1;
					break;
				}
			}
		}
		for (size_t i = 0; i < order.getPizzas().size(); ++i) {
			vector<Pizza> pizzas = order.getPizzas();
			pizzas.at(i).setID(id++);
			order.setPizzas(pizzas);
		}
	}
	catch (FailedOpenFile) {
		order.setID(1);
		size_t id = 1;
		for (size_t i = 0; i < order.getPizzas().size(); ++i) {
			vector<Pizza> pizzas = order.getPizzas();
			pizzas.at(i).setID(id++);
			order.setPizzas(pizzas);
		}
	}
}
