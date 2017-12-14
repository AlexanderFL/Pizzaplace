#pragma once

#include "ManagerService.h"
#include "CommonUI.h"

using namespace std;

class ManagerUI: public CommonUI
{
private:
	char input; //
	ManagerService service;
	//Toppings
	void showToppingsMenu();
	void showToppingCreationMenu();
	void showToppingDeleteMenu();
	void showToppingViewMenu();
	//Locations
	void showLocationsMenu();
	void showLocationCreationMenu();
	void showLocationDeleteMenu();
	void showLocationViewMenu();
	//Sizes
	void showSizeMenu();
	void showSizeCreationMenu();
	void showSizesDeleteMenu();
	void showSizeViewMenu();
	//Crust
	void showCrustMenu();
	void showCrustCreationMenu();
	void showSCrustDeleteMenu();
	void showCrustViewMenu();
	//Sides
	void showSidesMenu();
	void showSidesCreationMenu();

	//offers
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

