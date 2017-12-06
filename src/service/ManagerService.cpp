#include "ManagerService.h"

ManagerService::ManagerService(){}

/*
	Add a new topping.
*/
void ManagerService::addTopping(const Topping& topping) {

	try
	{
		string toppingName = topping.getName();
		// Check if string contains only alpha characters
		for (int i = 0; i < toppingName.length; i++){
			if (!isalpha(toppingName[i])){
				throw NumberInString();
			}
		}
		// Check if number is not less than or equal to zero
		if (topping.getPrice <= 0) {
			throw InvalidPrice();
		}

		repo.WriteToFile(topping);
	}
	catch (NumberInString)
	{
		cout << "Error: There was a number in the name" << endl;
	}
	catch (InvalidPrice)
	{
		cout << "Error: Price can not be less than or equal to zero" << endl;
	}
}

/*
	Add a new side order
*/
void ManagerService::addSideOrder(const SideOrder& side) {
	//Validate sideorder

	//repo.WriteTofile(side);
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