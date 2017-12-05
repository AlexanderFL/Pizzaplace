#include "ManagerUI.h"
#include "../model/Topping.h"
#include "../data/Data.h"
#include "../model/SideOrder.h"
#include "DeliveryUI.h"
ManagerUI::ManagerUI()
{
}

void ManagerUI::managerMenu() {
	string registration;
	bool ignore = true;
	while (true) {
		cout << "\n\t----------------------------\n"
			 << " \t|  1: Pizza |  2: Toppings |\n"
			 << " \t----------------------------\n"
			 << " \t|  3: Price |  4: Delivery |\n"
			 << " \t----------------------------\n"
			 << " \t|  5: Other |  6: Quit     |\n"
			 << " \t----------------------------\n" << endl;

		cout << "What would you like to register? ";
		if (ignore) {
			cin.ignore();
			ignore = false;
		}

		getline(cin, registration);
		//String size set to lower
		transform(registration.begin(), registration.end(), registration.begin(), ::tolower);

		if (registration == "pizza" || registration == "1") {
			cout << "a";
		}
		else if (registration == "toppings" || registration == "2") {
			//TODO: fix and add (also be able to delete a toping)
			int numberOfToppings;
			Data toppingRepo;
			Topping topping;
			cout << "How many topings would you like to add? ";
			cin >> numberOfToppings;
			cout << "What would you like as a topping? " << endl;

			//TODO: FIX LOOP
			string toppings;
			for (int i = 0; i < numberOfToppings; ++i) {
				cout << "Topping number " << i + 1 << ": ";
				cin >> toppings;
				toppingRepo.WriteToFile(topping);
			}
		}

		else if (registration == "price" || registration == "3") {
			//TODO: get the total price of an order
		} 
		else if (registration == "delivery" || registration == "4") {
			bool ignore = false;
			DeliveryUI deliveryUI;
			deliveryUI.setIgnore(ignore);
			deliveryUI.deliveryMenu();
		}
		else if (registration == "other" || registration == "5") {
			SideOrder sideOrder;
			cout << sideOrder;
		}
		else if (registration == "quit" || registration == "6") {
			break;
		}
		cin.clear();
		cin.sync();
	}
}