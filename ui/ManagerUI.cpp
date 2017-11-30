#include "ManagerUI.h"


ManagerUI::ManagerUI()
{
}

void ManagerUI::managerMenu() {
	string registration;
	bool ignore = true;
	while (true) {
		cout << "\n\t----------------------------\n"
			 << " \t|  Pizza: P |  Toppings: T |\n"
			 << " \t----------------------------\n"
			 << " \t|  Price: K |  Delivery: D |\n"
			 << " \t----------------------------\n"
			 << " \t|  Other: O |  Quit: Q     |\n"
			 << " \t----------------------------\n" << endl;

		cout << "What would you like to register? ";
		if (ignore) {
			cin.ignore();
			ignore = false;
		}
		getline(cin, registration);
		//so that it doesn't matter if the string is all caps or not
		transform(registration.begin(), registration.end(), registration.begin(), ::tolower);

		if (registration == "pizza" || registration == "p") {
			cout << "hg";
			break;
		}
		cin.clear();
		cin.sync();
	}
}