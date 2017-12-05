#include "SalesmanUI.h"
#include "DeliveryUI.h"
#include "../model/Order.h"

SalesmanUI::SalesmanUI()
{

}

void SalesmanUI::salesmanMenu() {
	bool ignore = true;
	string option;

	while (true) {
		cout << "\n\t--------------------------------------------------\n"
			<< " \t|  1: Register an Order   | 2: Add another order |\n"
			<< " \t--------------------------------------------------\n"
			<< " \t|  3: Price of the order  | 4: Home address      |\n"
			<< " \t--------------------------------------------------\n"
			<< " \t|  5: Food delivered      | 6: Food picked up    |\n"
			<< " \t--------------------------------------------------\n"
			<< " \t|  7: Mark paid for       | 8: Comments          |\n"
			<< " \t--------------------------------------------------\n"
			<< " \t|  9: Quit                |                      |\n"
			<< " \t--------------------------------------------------\n" << endl;
		
		cout << "What would you like to do? "; 

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