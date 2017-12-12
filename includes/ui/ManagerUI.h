#include <iostream>
#include <string>
#include <algorithm>
#include "ManagerService.h"
#include "Topping.h"
#include "Data.h"
#include "SideOrder.h"
#include "DeliveryUI.h"
#include "CommonUI.h"
#include "Order.h"
#include "Location.h"
//For clearing the screen
#include <stdlib.h>
using namespace std;

class ManagerUI: CommonUI
{
private:
	char input;  //<----- shouldn't be here
	ManagerService service;
	void pizzaOption();
	void toppingOption();
	void priceOption();
	void locationOption();
	void sideOrderOption();
public:
	ManagerUI();
	void managerMenu();
	//Pizza
	void validateSizeOptions();
	void validateCrustOptions();
	void validateCrustInput(char input);
	void addingMultipleCrusts();
	void deleteMultipleCrusts();
	void seeAllCrust();
	void addSizeMenu();
	void deleteSizeMenu();
	void seeAllSizesMenu();
	//Side orders
	void validateOtherInput(char input);
	void addMultipleSides();
	void deleteMultipleSides();
	void seeAllSides();
	//Toppings
	void validateToppingInput(char input);
	void addMultipleToppings();
	void deleteToppings();
	void seeAllToppings();
	//Location
	void addingMultipleLocations();
	void validateLocationOptions(char input);
	void deleteMultipleLocations();
	void seeAllLocations();
	//Pizza Menu
	void pizzaMenuOption();
	void validatePizzaMenuOption(char input);
	void addMultiplePizza();
	void seePizzaMenu();
	void deletePizzaOnMenu();
};

