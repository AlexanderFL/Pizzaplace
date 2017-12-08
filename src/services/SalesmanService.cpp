#include "SalesmanService.h"


SalesmanService::SalesmanService()
{
	_repo = Data();
}

void SalesmanService::registerNewOrder(Order& order)
{
	// TODO: Checks to validate input
	if (validateOrder(order)) {
		_repo.WriteToFile(order);
	}
	else {
		throw InvalidOrder();
	}
}

void SalesmanService::appendToOrder(Order& firstOrder, Order& secondOrder)
{
	// TODO: Checks to validate input from both orders
	if (validateOrder(firstOrder) && validateOrder(secondOrder)) {
		firstOrder = firstOrder + secondOrder;
	}
	else {
		throw InvalidOrder();
	}
}

int SalesmanService::getPriceOfOrder(Order& order)
{
	int price = calculateCost(order);
	return price;
}

void SalesmanService::assignHomeAddress(Order& order, string address)
{
	order.setHomeAddress(address);
}

void SalesmanService::setOrderToDelivery(Order& order)
{
	order.setDeliveryMethod(SEND);
}

void SalesmanService::setOrderAsPaid(Order& order)
{
	order.setOrderAsPaidFor(true);
}

void SalesmanService::setComments(Order& order, string comment)
{
	order.setComment(comment);
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
		int temptotal = 0;
		size_t numberOfToppingsOnPizza = order.getPizzas().at(i).getToppings().size();
		for (size_t j = 0; j < numberOfToppingsOnPizza; ++j) {
			temptotal += order.getPizzas().at(i).getToppings().at(j).getPrice(); // Add each topping to price
		}
		temptotal += order.getPizzas().at(i).getCrust().getPrice(); // Add type of crust to price
		temptotal *= order.getPizzas().at(i).getPizzaSize().getPriceMod(); // Add the pizza size to price
		total += temptotal;
	}
	// Side orders cost
	for (int i = 0; i < order.getSides().size(); ++i) {
		total += order.getSides().at(i).getPrice();

	}
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