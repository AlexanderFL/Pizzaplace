#include "SalesmanService.h"


SalesmanService::SalesmanService()
{
	_repo = Data();
}

void SalesmanService::registerNewOrder(Order& order)
{
	if (validateOrder(order)) {
		assignID(order);
		_repo.WriteToFile(order);
	}
	else {
		throw InvalidOrder();
	}
}

void SalesmanService::appendToOrder(Order& firstOrder, Order& secondOrder)
{
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
void SalesmanService::appendToOrder(Order& firstOrder, Pizza &pizza)
{
	// Get the pizzas from a order
	vector<Pizza> pizzaVector = firstOrder.getPizzas();
	// Append the pizza given in parameter
	pizzaVector.push_back(pizza);
	// Set the vector back in order
	firstOrder.setPizzas(pizzaVector);
}

// Appends sides to a order
void SalesmanService::appendToOrder(Order& order, SideOrder &sideAppend)
{
	vector<SideOrder> sidesVector = order.getSides();
	sidesVector.push_back(sideAppend);
	order.setSides(sidesVector);
}

Pizza SalesmanService::getPizza()
{
	return _pizza;
}

int SalesmanService::getPriceOfOrder(Order& order)
{
	int price = calculateCost(order);
	return price;
}

int SalesmanService::getOldPriceOfOrder(Order& order)
{
	int price = calculateOldCost(order);
	return price;
}

void SalesmanService::assignHomeAddress(Order& order, string address)
{
	//address must contain at least one character and one number
	//ex. of address: 'Menntavegur 1' or 'Skogarstigur 12'
	//
	//address can be empty if deliverymethod is pickup
	bool containsCharacter = false;
	bool containsNumber = false;
	if (address == "" && order.getDeliveryMethod() == PICKUP) {
		order.setHomeAddress(address);
	}
	else
	{
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

void SalesmanService::validInput(const char& input, const int& max, const int& min) const
{
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

SideOrder SalesmanService::getSideOrder()
{
	return _sides;
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
				int temptotal = 0;
				for (size_t j = 0; j < order.getPizzas().at(i).getToppings().size(); ++j) {
					temptotal += order.getPizzas().at(i).getToppings().at(j).getPrice();
				}
				temptotal += order.getPizzas().at(i).getCrust().getPrice();
				temptotal *= order.getPizzas().at(i).getPizzaSize().getPriceMod();
				total += temptotal;
			}
			for (size_t i = 0; i < order.getSides().size(); ++i) {
				total += order.getSides().at(i).getPrice();
			}
			total *= (comps.at(0).getPrice() / 100.0);
			return total;
			//return comps.at(0).getPrice();
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
			tempExt.erase(tempExt.begin());
		}
	}
	for (size_t k = 0; k < ext.size(); ++k) {
		//total += ext.at(i).getPrice();
		int exttotal = 0;
		for (size_t i = 0; i < ext.at(k).getOrder().getPizzas().size(); ++i) {
			int temptotal = 0;
			for (size_t j = 0; j < ext.at(k).getOrder().getPizzas().at(i).getToppings().size(); ++j) {
				temptotal += ext.at(k).getOrder().getPizzas().at(i).getToppings().at(j).getPrice();
			}
			temptotal += ext.at(k).getOrder().getPizzas().at(i).getCrust().getPrice();
			temptotal *= ext.at(k).getOrder().getPizzas().at(i).getPizzaSize().getPriceMod();
			exttotal += temptotal;
		}
		for (size_t i = 0; i < ext.at(k).getOrder().getSides().size(); ++i) {
			exttotal += ext.at(k).getOrder().getSides().at(i).getPrice();
		}
		exttotal *= (ext.at(k).getPrice() / 100.0);
		total += exttotal;
		temp = temp - ext.at(k).getOrder();
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
			//double temp = (singles.at(i).getOrder().getPizzas().at(0) * pizza).getToppings().size() / (sqrt(singles.at(i).getOrder().getPizzas().at(0).getToppings().size()) * sqrt(pizza.getToppings().size()));
			if (sim < temp) {
				sim = temp;
				index = i;
			}
		}
	}
	/*if (index == -1) {
		//normal
		for (size_t i = 0; i < pizza.getToppings().size(); ++i) {
			total += pizza.getToppings().at(i).getPrice();
		}
	}
	else {
		total += singles.at(index).getPrice();
		if (pizza != singles.at(index).getOrder().getPizzas().at(0)) {
			Pizza temp = pizza - singles.at(index).getOrder().getPizzas().at(0);
			for (size_t i = 0; i < temp.getToppings().size(); ++i) {
				total += temp.getToppings().at(i).getPrice();
			}
		}
	}*/
	if (index == -1) {
		//normal
		for (size_t i = 0; i < pizza.getToppings().size(); ++i) {
			total += pizza.getToppings().at(i).getPrice();
		}
		total += pizza.getCrust().getPrice();
		total *= pizza.getPizzaSize().getPriceMod();
		return total;
	}
	else {
		Pizza extras = pizza - singles.at(index).getOrder().getPizzas().at(0);
		Pizza specials = pizza - extras;
		for (size_t i = 0; i < specials.getToppings().size(); ++i) {
			total += pizza.getToppings().at(i).getPrice();
		}
		total += pizza.getCrust().getPrice();
		total *= pizza.getPizzaSize().getPriceMod();
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
	return ((left * right).getPizzas().size() + (left * right).getSides().size()) / ((sqrt(left.getPizzas().size()) * sqrt(right.getPizzas().size())) + (sqrt(left.getSides().size()) * sqrt(right.getSides().size())));
}

double SalesmanService::pizzaSimularity(const Pizza& left, const Pizza& right) {
	return (left * right).getToppings().size() / (sqrt(left.getToppings().size()) * sqrt(right.getToppings().size()));
}

/*
=======
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
int SalesmanService::calculateOldCost(const Pizza& pizza) {
	int total = 0;
	size_t numberOfToppingsOnPizza = pizza.getToppings().size();
	for (size_t j = 0; j < numberOfToppingsOnPizza; ++j) {
		total += pizza.getToppings().at(j).getPrice(); // Add each topping to price
	}
	total += pizza.getCrust().getPrice(); // Add type of crust to price
	total *= pizza.getPizzaSize().getPriceMod(); // Multiply the pizza size mod to price
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
