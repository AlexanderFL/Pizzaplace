#include "SalesmanUI.h"
#include "DeliveryUI.h"
#include "../model/Order.h"
#include "Menu.h"
SalesmanUI::SalesmanUI()
{

}

void SalesmanUI::salesmanMenu() {
	bool ignore = true;
	string option;
	Menu menu;
	while (true) {
		cout << menu.printMenu({ "Register an order", "Add another order", "Price of the order", "Home address", "Food delivered", "Food picked up", "Mark paid for", "Comments" }) << endl;
		cout << "Press 'q' to quit.\nWhat would you like to do? "; 

		if (ignore) {
			cin.ignore();
			ignore = false;
		}
		getline(cin, option);

		//so that it doesn't matter if the string is all caps or not
		transform(option.begin(), option.end(), option.begin(), ::tolower);
		cout << endl;
		//TODO: Fix the look of these statements and add functions to them
		if (option == "1" || option == "2") {
			Order order;
			order.MakeOrder();
			break;
		}
		else if (option == "3") {
			Order order;
			double totalCost = order.getTotalCost();
			cout << "The total cost is: " << totalCost << " kr" << endl;
			break;
		}
		else if (option == "4") {
			break;
		}
		else if (option == "5") {
			break;
		}
		else if (option == "6") {
			break;
		}
		else if (option == "7") {
			break;
		}
		else if (option == "8") {
			break;
		}
		else if (option == "9" || option == "q") {
			break;
		}

		cin.clear();
		cin.sync();
	}
}