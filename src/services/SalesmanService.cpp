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


/*			Returns total cost for the order		*/
int SalesmanService::calculateCost(const Order& order) {
	int total = 0;
	size_t numberOfPizzas = order.getPizzas().size();
	// Pizza cost
	for (size_t i = 0; i < numberOfPizzas; ++i) {
		total += calculateCost(order.getPizzas().at(i));
	}
	// Side orders cost
	for (int i = 0; i < order.getSides().size(); ++i) {
		total += order.getSides().at(i).getPrice();

	}
	return total;
}

/*			Returns total cost for the pizza		*/
int SalesmanService::calculateCost(const Pizza& pizza) {
	int total = 0;
	size_t numberOfToppingsOnPizza = pizza.getToppings().size();
	for (size_t j = 0; j < numberOfToppingsOnPizza; ++j) {
		total += pizza.getToppings().at(j).getPrice(); // Add each topping to price
	}
	total += pizza.getCrust().getPrice(); // Add type of crust to price
	total *= pizza.getPizzaSize().getPriceMod(); // Multiply the pizza size mod to price
	return total;
}

/*			Validate the Order			*/
bool SalesmanService::validateOrder(Order order) {
	// Just check if both pizzas and sides vectors are emtpy
	if (order.getPizzas().empty() && order.getSides().empty()) {
		return false;
	}
	return true;
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