#include "ManagerService.h"

ManagerService::ManagerService(){}

/*		Add a new topping.		*/
void ManagerService::addTopping(const Topping& topping) {
	// Validate topping
	string toppingName = topping.getName();
	if (containsOnlyAlpha(toppingName) == false) {
		throw NumberInString();
	}
	if (validPrice(topping.getPrice()) == false) {
		throw InvalidPrice();
	}
	// Write it to file
	repo.WriteToFile(topping);
}

/*		Add a new side order		*/
void ManagerService::addSideOrder(const SideOrder& side) {
	// Validate side order
	string sideOrderName = side.getName();
	if (containsOnlyAlpha(sideOrderName) == false) {
		throw NumberInString();
	}
	if (validPrice(side.getPrice())){
		throw InvalidPrice();
	}

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

int ManagerService::getOrderTotalCost(const Order& order) {
	int total = 0;
	for (int i = 0; i < order.getPizzas().size(); ++i) {
		int temptotal = 0;
		for (int j = 0; j < order.getPizzas().at(i).getToppings().size(); ++j) {
			temptotal += order.getPizzas().at(i).getToppings().at(j).getPrice();
			
		}
		temptotal += order.getPizzas().at(i).getCrust().getPrice();
		temptotal *= order.getPizzas().at(i).getPizzaSize().getPriceMod();
		total += temptotal;
		
	}
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
bool ManagerService::containsOnlyAlpha(string s)
{
	for (int i = 0; i < s.length(); i++) {
		if (!isalpha(s[i])) {
			return false;
		}
	}
	return true;
}

/*
		Checks if price is valid, a price is valid if it is
		not a number below zero.
*/
bool ManagerService::validPrice(double p)
{
	if (p < 0.0) {
		return false;
	}
	return true;
}
