#include "SalesmanUI.h"
#include "DeliveryUI.h"
#include "Order.h"
#include "SalesmanService.h"
#include <stdlib.h>

SalesmanUI::SalesmanUI()
{

}

void SalesmanUI::salesmanMenu() {
	string option;
	Menu menu;
	char input;
	while (true) {
		cout << menu.printMenu({ "Register an order", "Go back" }) << endl;
		cout << "Press 'q' to quit.\nWhat would you like to do? "; 

		cin.ignore();
		cin >> input;

		system("CLS");

		switch (input) {
		case '1':
			makeNewOrder();
			break;
		case '2':
			return;
		case 'q':
		case 'Q':
			exit(1);
		}
	}
}
//Let the user pick from menu
void SalesmanUI::makeNewOrder()
{
	Order order;
	SalesmanService service;
	char input;
	int i = 1;
	cout << "Welcome! Please pick a Pizza location from one of the following:" << endl;
	vector<Location> locations = service.getAll<Location>();
	for (unsigned int i = 0; i < locations.size(); i++) {
		cout << i + 1 << ": " << locations.at(i).getAddress() << endl;
	}
	cout << "Input: ";
	cin >> input;
	order.setLocation(locations.at((int)input - 49));
	while (true) {
		try
		{
			Pizza pizza;
			cout << "Order number " << i << "." << endl;
			// Select type of crust
			vector<PizzaCrust> crusts = service.getAllPizzaCrusts();
			cout << "Here are the crusts you can choose from:" << endl;
			for (size_t i = 0; i < crusts.size(); ++i) {
				cout << i + 1 << ": " << crusts.at(i).getName() << endl;
			}
			cout << "Please choose one of them. \nInput: ";
			cin >> input;
			pizza.setCrust(crusts.at((int)input - 49));

			// Select the size of the pizza
			vector<PizzaSize> sizes = service.getAllPizzaSizes();
			cout << "Here are the sizes you can choose from:" << endl;
			for (size_t i = 0; i < sizes.size(); ++i) {
				cout << i + 1 << ": " << sizes.at(i).getName() << endl;
			}
			cout << "Please choose one of them. \nInput: ";
			cin >> input;
			pizza.setPizzaSize(sizes.at((int)input - 49));

			// Select all toppings
			vector<Topping> toppings = service.getAllToppings();
			while (true)
			{
				cout << "Here are the toppings you can choose from:" << endl;
				for (size_t i = 0; i < toppings.size(); ++i) {
					cout << i + 1 << ": " << toppings.at(i).getName() << endl;
				}
				cout << "How many toppings would you like? ";
				cout << "\nPlease enter 0 if you wish to have no toppings.\nInput: ";
				char numberOfToppings;
				cin >> numberOfToppings;
				int numberOfToppingsInt = (int)numberOfToppings - 48;
				for (int i = 0; i < numberOfToppingsInt; i++) {
					cout << "Topping number " << i + 1 << " is: ";
					cin >> input;
					if ((int)input - 48 == (toppings.size() + 1)) {
						break;
					}
					pizza.addToppings(toppings.at((int)input - 49));
				}
				break;
			}
			
			service.appendToOrder(order, pizza);
			// Ask user if he wants any sides
			cout << endl << "Would you like any sides with your order? Y/N (yes/no): ";
			cin >> input;
			if (toupper(input) == 'Y') {
				cout << "Here are side orders you can choose from: " << endl;
				vector<SideOrder> sideOrder = service.getAllSideOrders();
				for (size_t i = 0; i < sideOrder.size(); i++)
				{
					cout << i + 1 << ": " << sideOrder.at(i).getName() << endl;
				}
				cout << "Please choose one of them. \nInput: ";
				cin >> input;
				
				//Set the selected side order in service
				int index = (int)input - 49;
				service.appendToOrder(order, sideOrder.at(index));
			}
		/*	cout << "Your order is:" << endl;
			string info = "A ";
			info += pizza.getPizzaSize().getName() + " pizza with ";
			if (toppings.size() == 0) {
				info += "no toppings, ";
			}
			else {
				for (size_t i = 0; i < toppings.size(); ++i) {
					info += toppings.at(i).getName() + ", ";
				}
			}*/
			cout << "Would you like to add another order to this?" << endl;
			cout << "Input (y/n): ";
			cin >> input;
			if (tolower(input) != 'y') {
				//Add the new order to file
				service.registerNewOrder(order);
				break;
			}
			cout << endl;
			i++;
		}
		catch (FailedOpenFile) {
			cout << "Failed to open a critical file...";
			break;
		}
	}
}


void SalesmanUI::pickFromMenu() {
	vector <Offer> offers = service.getAll<Offer>();
		cout << "	PIZZA MENU!" << endl;
		for (unsigned int i = 0; i < offers.size(); i++) {
			cout << endl;
			cout << "Pizzan nr." << i + 1 << ": " << endl;
			cout << offers.at(i);
			cout << "Toppings: ";
			for (unsigned int j = 0; j < offers.at(i).getOrder().getPizzas().size(); j++) {
				cout << offers.at(i).getOrder().getPizzas().at(j) << endl;
			}
}