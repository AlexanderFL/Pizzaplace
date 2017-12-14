#include "ManagerService.h"

ManagerService::ManagerService(){}

/*		Add a new topping.		*/
void ManagerService::addTopping(Topping& topping) {
	// Validate topping
	string toppingName = topping.getName();
	containsOnlyAlpha(toppingName);
	validPrice(topping.getPrice());
	//Write it to file
	repo.WriteToFile(topping);
}

/*		Add a new side order		*/
void ManagerService::addSideOrder(SideOrder& side) {
	// Validate side order
	string sideOrderName = side.getName();
	validPrice(side.getPrice());
	repo.WriteToFile(side);
}
/*		Adding a crust		*/
void ManagerService::addCrust(PizzaCrust& crust) {
	// Validate crust
	string crustName = crust.getName();
	containsOnlyAlpha(crustName);
	validPrice(crust.getPrice());
	repo.WriteToFile(crust);
}

/*		Add a new offer				*/
void ManagerService::addOffer(Offer& offer) {
	// Validate offer
	string offerName = offer.getName();
	validPrice(offer.getPrice());
	repo.WriteToFile(offer);
}

/*		Add new special offer for the menu.		*/
void ManagerService::addSpecialOrder(string ordername, const Order & order){
	// No special checks needed
	Offer offer(ordername, order, 0, true);
	repo.WriteToFile(offer);
}

/*		Add new delivery places		*/
void ManagerService::addDeliveryPlace(string address){
	Location l(address);
	repo.WriteToFile(l);
}

/*		Add new location places		*/
void ManagerService::addLocation(Location& location) {
	//Validate location 
	string locationName = location.getAddress();
	containsOnlyAlpha(locationName);
	repo.WriteToFile(location);
}

/*		Returns total cost for the order		*/
int ManagerService::getOrderTotalCost(const Order& order) {
	int total = 0;
	size_t numberOfPizzas = order.getPizzas().size();
	// Pizza cost
	for (size_t i = 0; i < numberOfPizzas; ++i) {
		int temptotal = 0;
		size_t numberOfToppingsOnPizza = order.getPizzas().at(i).getToppings().size();
		// Add each topping to the price
		for (size_t j = 0; j < numberOfToppingsOnPizza; ++j) {
			temptotal += order.getPizzas().at(i).getToppings().at(j).getPrice();
		}
		// Add type of crust to the price
		temptotal += order.getPizzas().at(i).getCrust().getPrice();
		// Add the pizza size to the price
		temptotal *= order.getPizzas().at(i).getPizzaSize().getPriceMod(); 
		total += temptotal;
	}
	// Side orders cost
	for (int i = 0; i < order.getSides().size(); ++i) {
		total += order.getSides().at(i).getPrice();
		
	}
	return total;
}

void ManagerService::replaceToppingInFile(const Topping & topping, int index){
	vector<Topping> toppings = repo.RetrieveAllFromFile<Topping>();
	toppings[index] = topping;
	repo.WriteMultipleLinesToFile<Topping>(toppings);
}

/*		Checks if string contains only alpha characters
Returns true if it does and false otherwise.

Examples for usage: If topping contains a number,
the function will return false,
because it is not a valid topping name.
*/
void ManagerService::containsOnlyAlpha(string s){
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

void ManagerService::validPrice(int p){
	if (p <= 0) {
		throw InvalidPrice();
	}
}

void ManagerService::validProcent(int p) {
	if (p <= 0 || p >= 100) {
		throw InvalidPrice();
	}
}

void ManagerService::validateOffer(const Offer& offer) {
	if (offer.getOrder().getPizzas().empty() && offer.getOrder().getSides().empty()) {
		throw InvalidOffer("Offer needs to have a pizza or side in it.");
	}
	if (offer.getPrice() == 0) {
		throw InvalidOffer("Price needs to be set.");
	}
	if (offer.getName() == "Unnamed") {
		throw InvalidOffer("Offer can't be Unnamed");
	}
}