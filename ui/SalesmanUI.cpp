#include "SalesmanUI.h"

SalesmanUI::SalesmanUI()
{

}

void SalesmanUI::salesmanMenu() {
	bool ignore = true;
	string option;
	while (true) {
		cout << "\n\t---------------------------------------------------\n"
			<< " \t|  Register a pizza: P    |  Add another order: A |\n"
			<< " \t---------------------------------------------------\n"
			<< " \t|  Price of the order: K  |  Delivery: D          |\n"
			<< " \t---------------------------------------------------\n"
			<< " \t|  Food delivered: L      |  Paid for: S          |\n"
			<< " \t---------------------------------------------------\n"
			<< " \t|  Home address: H        |  Comments: C          |\n"
			<< " \t---------------------------------------------------\n"
			<< " \t|  Quit : Q               |                       |\n"
			<< " \t---------------------------------------------------\n" << endl;
		
		cout << "What would you like to do? "; 
		if (ignore) {
			cin.ignore();
			ignore = false;
		}
		getline(cin, option);

		//so that it doesn't matter if the string is all caps or not
		transform(option.begin(), option.end(), option.begin(), ::tolower);

		if (option == "quit" ||option == "q") {
			break;
		}
		cin.clear();
		cin.sync();
	}
}