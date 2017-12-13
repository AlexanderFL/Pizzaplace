#pragma once

#include "ManagerService.h"
#include "CommonUI.h"

using namespace std;

class ManagerUI: public CommonUI
{
private:
	char input;  //<----- shouldn't be here
	ManagerService service;
	void showToppingsMenu();
	void showToppingCreationMenu();
	void showToppingViewMenu();
	void showToppingDeleteMenu();

	void showOffersMenu();
	void showOfferCreationMenu();
	void showOfferViewMenu();
	void showOfferDeleteMenu();
	void showCreatePizzaMenu(Pizza& pizza);
	void pizzaOption();
	void toppingOption();
	void priceOption();
	void locationOption();
	void sideOrderOption();
public:
	ManagerUI();
	void showMainMenu();
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
	void editTopping(vector<Topping> toppings, int index);
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

