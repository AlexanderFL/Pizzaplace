#pragma once
#include "ManagerService.h"
#include "CommonUI.h"
#include "Canceled.h"

class ManagerUI : public CommonUI
{
private:
	ManagerService service;
public:
	ManagerUI();
	void
		showMainMenu();
private:
	/*		Toppings		*/
	void showToppingsMenu();
	void showToppingCreationMenu();
	void showToppingDeleteMenu();
	void showToppingViewMenu();
	void editTopping(int index);

	/*		Locations		*/
	void showLocationsMenu();
	void showLocationCreationMenu();
	void showLocationDeleteMenu();
	void showLocationViewMenu();

	/*		Sizes			*/
	void showSizeMenu();
	void showSizeCreationMenu();
	void showSizesDeleteMenu();
	void showSizeViewMenu();

	/*		Crusts			*/
	void showCrustMenu();
	void showCrustCreationMenu();
	void showCrustDeleteMenu();
	void showCrustViewMenu();

	/*		Sides			*/
	void showSidesMenu();
	void showSidesCreationMenu();
	void showSidesDeleteMenu();
	void showSidesViewMenu();

	/*		Offers			*/
	void showOffersMenu();
	void showOfferCreationMenu();
	void showOfferViewMenu();
	void showOfferDeleteMenu();
	void showCreatePizzaMenu(Pizza &pizza);

	/*		Orders			*/
	void showOrders();
};

