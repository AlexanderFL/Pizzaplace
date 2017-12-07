#include "ManagerService.h"

ManagerService::ManagerService(){}

/*		Add a new topping.		*/
void ManagerService::addTopping(const Topping& topping) {
	// Validate topping
	string toppingName = topping.getName();
	containsOnlyAlpha(toppingName);
	validPrice(topping.getPrice());
	// Write it to file
	repo.WriteToFile(topping);
}

/*		Add a new side order		*/
void ManagerService::addSideOrder(const SideOrder& side) {
	// Validate side order
	string sideOrderName = side.getName();

	validPrice(side.getPrice());

	// Write it to file
	repo.WriteToFile(side);
}

/*		Add new special offer for the menu.		*/
void ManagerService::addSpecialOrder(string ordername, const Order & order)
{
	// No special checks needed
	Offer offer(ordername, order, 0, true);

	repo.WriteToFile(offer);
}

/*		Add new delivery places		*/
void ManagerService::addDeliveryPlace(string address)
{
	Location l(address);
	repo.WriteToFile(l);
}

/*			Get all toppings		*/
vector<Topping> ManagerService::getToppings() {
	return repo.RetrieveAllFromFile<Topping>();
}

/*			Delete topping			*/
void ManagerService::deleteTopping(int index) {
	repo.RemoveFromFileAtIndex<Topping>(index);
}

/*			Delete a side order		*/
void ManagerService::deleteSideOrder(int index) {
	repo.RemoveFromFileAtIndex<SideOrder>(index);
}

/*			Returns total cost for the order		*/
int ManagerService::getOrderTotalCost(const Order& order) {
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

/*
*************************************************
*****			PRIVATE FUNCTIONS			*****
*************************************************
*/

/*		Checks if string contains only alpha characters
		Returns true if it does and false otherwise.
		
		Examples for usage: If topping contains a number,
							the function will return false,
							because it is not a valid topping name.
*/
void ManagerService::containsOnlyAlpha(string s)
{
	for (int i = 0; i < s.length(); i++) {
		if (!isalpha(s[i])) {
			throw NumberInString();
		}
	}
}

/*
		Checks if price is valid, a price is valid if it is
		not a number below zero.
*/
void ManagerService::validPrice(int p)
{
	if (p < 0) {
		throw InvalidPrice();
	}
}
