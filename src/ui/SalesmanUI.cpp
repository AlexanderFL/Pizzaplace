#include "SalesmanUI.h"
#include "DeliveryUI.h"
#include "Order.h"
#include "Menu.h"
#include <stdlib.h>
SalesmanUI::SalesmanUI()
{

}

void SalesmanUI::salesmanMenu() {
	bool ignore = true;
	string option;
	Menu menu;
	char input;
	bool stillSalesman = true;
	while (stillSalesman) {
		system("CLS");
		cout << menu.printMenu({ "Register an order", "Add another order", "Price of the order", "Home address", "Food delivered", "Food picked up", "Mark paid for", "Comments", "Go back" }) << endl;
		cout << "Press 'q' to quit.\nWhat would you like to do? "; 

		if (ignore) {
			cin.ignore();
			ignore = false;
		}
		cin >> input;

		switch (input) {
		case '1':
		case '2':{
			Order order;
			order.MakeOrder();
			break;
		}
		case '3': {
			Order order;
			double totalCost = order.getTotalCost();
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