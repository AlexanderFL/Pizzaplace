#include "SalesmanService.h"


SalesmanService::SalesmanService()
{
	_repo = Data();
}

void SalesmanService::registerNewOrder(Order& order)
{
	
}

void SalesmanService::appendToOrder(Order& order)
{

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
	int numberOfPizzas = order.getPizzas().size();
	// Pizza cost
	for (int i = 0; i < numberOfPizzas; ++i) {
		int temptotal = 0;
		int numberOfToppingsOnPizza = order.getPizzas().at(i).getToppings().size();
		for (int j = 0; j < numberOfToppingsOnPizza; ++j) {
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