#include "ManagerUI.h"


ManagerUI::ManagerUI()
{
}

void ManagerUI::managerMenu() {
	string registration;
	while (true) {
		cout << "-----------------------\n"
			<< "|  Pizza |  Toppings | \n"
			<< "-----------------------\n"
			<< "|  Price |  Delivery | \n"
			<< "-----------------------\n"
			<< "|  Other |   Quit    | \n"
			<< "-----------------------\n" << endl;

		cout << "What would you like to register? ";
		cin.ignore();
		getline(cin, registration);
		transform(registration.begin(), registration.end(), registration.begin(), ::tolower);
		if (registration == "pizza") {
			cout << "hg";
			break;
		}
	}
}