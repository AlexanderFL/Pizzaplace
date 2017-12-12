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
		cout << menu.printMenu({ "Register an order", "Add another order", "Price of the order", "Home address", "Food delivered", "Food picked up", "Mark paid for", "Comments", "Go back" }) << endl;
		cout << "Press 'q' to quit.\nWhat would you like to do? "; 

		cin.ignore();
		cin >> input;

		system("CLS");

		switch (input) {
		case '1':
			makeNewOrder();
			break;
		case '2':{
			makeNewOrder();
			break;
		}
		case '3': {
			Order order;
			//Todo replace with service
			double totalCost = 0;//order.getTotalCost();
			cout << "The total cost is: " << totalCost << " kr" << endl;
			break;
		}
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return;
		case 'q':
		case 'Q':
			exit(1);
		}
	}
}

void SalesmanUI::makeNewOrder()
{
	SalesmanService service;
	char input;
	while (true) {
		try
		{
			vector<Topping> toppings = service.getAllToppings();
			cout << "Here are the toppings you can choose from:" << endl;
			for (size_t i = 0; i < toppings.size(); ++i) {
				cout << i + 1 << ": " << toppings.at(i).getName() << endl;
			}
			cout << "Please choose one of them. \nInput: ";
			cin >> input;

			service.getPizza().getToppings().push_back(toppings.at((int)input - 49));

			vector<PizzaCrust> crusts = service.getAllPizzaCrusts();
			cout << "Here are the crusts you can choose from:" << endl;
			for (size_t i = 0; i < crusts.size(); ++i) {
				cout << i + 1 << ": " << crusts.at(i).getName();
			}
			cout << "Please choose one of them. \nInput: ";
			cin >> input;
			service.getPizza().setCrust(crusts.at((int)input - 49));

			vector<PizzaSize> sizes = service.getAllPizzaSizes();
			cout << "Here are the sizes you can choose from:" << endl;
			for (size_t i = 0; i < sizes.size(); ++i) {
				cout << i + 1 << ": " << sizes.at(i).getName();
			}
			cout << "Please choose one of them. \nInput: ";
			cin >> input;
			service.getPizza().setPizzaSize(sizes.at((int)input - 49));
		}
		catch (FailedOpenFile) {
			cout << "Failed to open a critical file...";
			break;
		}
	}
}
