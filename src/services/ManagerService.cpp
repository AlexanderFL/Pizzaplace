#include "ManagerService.h"

ManagerService::ManagerService(){}

/*		Add a new topping.		*/
void ManagerService::addTopping(Topping& topping) {
	// Validate topping
	string toppingName = topping.getName();
	containsOnlyAlpha(toppingName);
	validPrice(topping.getPrice());
	// Write it to file
	assignID(topping);
	repo.WriteToFile(topping);
}

/*		Add a new side order		*/
void ManagerService::addSideOrder(SideOrder& side) {
	// Validate side order
	string sideOrderName = side.getName();

	validPrice(side.getPrice());

	// Write it to file
	assignID(side);
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
	assignID(l);
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

/*			Delete a Location		*/
void ManagerService::deleteLocation(int index) {
	repo.RemoveFromFileAtIndex<Location>(index);
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

//Adding locations
void ManagerService::addLocation(Location& location) {
	//Validate location 
	string locationName = location.getAddress();
	containsOnlyAlpha(locationName);
	// Write it to file
	assignID(location);
	repo.WriteToFile(location);
}

vector<Location>ManagerService::getLocations() {
	vector<Location> locations = repo.RetrieveAllFromFile<Location>();
	/*if (locations.size() == 0) {
		throw EmptyVector();
	}*/
	return locations;
}

//Getting side Orders
vector<SideOrder> ManagerService::getSides() {
	vector<SideOrder> sides = repo.RetrieveAllFromFile<SideOrder>();
	/*if (sides.size() == 0) {
		throw EmptyVector();
	}*/
	return sides;
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


void ManagerService::assignID(Topping& topping) {
	try {
		vector<Topping> toppings = repo.RetrieveAllFromFile<Topping>();
		if (toppings.size() == 0) {
			topping.setID(1);
		}
		else {
			topping.setID(toppings.at(toppings.size() - 1).getID() + 1);
		}
	}
	catch (FailedOpenFile) {
		topping.setID(1);
	}
}

void ManagerService::assignID(SideOrder& side) {
	try {
		vector<SideOrder> sides = repo.RetrieveAllFromFile<SideOrder>();
		if (sides.size() == 0) {
			side.setID(1);
		}
		else {
			side.setID(sides.at(sides.size() - 1).getID() + 1);
		}
	}
	catch (FailedOpenFile) {
		side.setID(1);
	}
}

void ManagerService::assignID(Offer& offer) {
	try {
		vector<Offer> offers = repo.RetrieveAllFromFile<Offer>();
		if (offers.size() == 0) {
			offer.setID(1);
		}
		else {
			offer.setID(offers.at(offers.size() - 1).getID() + 1);
		}
	}
	catch (FailedOpenFile) {
		offer.setID(1);
	}
}

void ManagerService::assignID(Location& loc) {
	try {
		vector<Location> locs = repo.RetrieveAllFromFile<Location>();
		if (locs.size() == 0) {
			loc.setID(1);
		}
		else {
			loc.setID(locs.at(locs.size() - 1).getID() + 1);
		}
	}
	catch (FailedOpenFile) {
		loc.setID(1);
	}
}