#include "ManagerService.h"

ManagerService::ManagerService(){}

/*
	Add a new topping.
*/
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

/*
	Add a new side order
*/
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

/*
	Add new special orders for the menu.
*/
void ManagerService::addSpecialOrder(string ordername, const Order & order)
{
	//Validate
}

/*
	Add new delivery places
*/
void ManagerService::addDeliveryPlace(string place)
{
	//Validate
}

vector<Topping> ManagerService::getToppings() {
	return repo.RetrieveAllFromFile<Topping>();
}


/*
*************************************************
*****			PRIVATE FUNCTIONS			*****
*************************************************
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

bool ManagerService::validPrice(double p)
{
	if (p <= 0.0) {
		return false;
	}
	return true;
}