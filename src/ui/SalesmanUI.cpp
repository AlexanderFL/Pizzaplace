#include "SalesmanUI.h"
#include "DeliveryUI.h"
#include "Order.h"
#include "Menu.h"
#include "SalesmanService.h"
#include <stdlib.h>
SalesmanUI::SalesmanUI()
{

}

void SalesmanUI::salesmanMenu() {
	string option;
	Menu menu;
	char input;
	bool stillSalesman = true;
	while (stillSalesman) {
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
			Order order;
			//Todo replace with service
			//order.MakeOrder();
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
			stillSalesman = false;
			break;
		case 'q':
		case 'Q':
			exit(1);
		}
	}
}

void SalesmanUI::makeNewOrder()
{
	SalesmanService service;
	Order newOrder;

	PizzaCrust newCrust;
	PizzaSize newSize;

	// TODO: Get all pizza sizes and crusts available and display them
	//		 for the salesman to select from.
}