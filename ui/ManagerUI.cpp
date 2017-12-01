#include "ManagerUI.h"
#include "../pizza/Topping.h"
#include "../pizza/ToppingRepository.h"
#include "../order/SideOrder.h"
#include "DeliveryUI.h"
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
			cout << "a";
			break;
		}
		else if (registration == "toppings" || registration == "t") {
			//TODO: fix and add (also be able to delete a toping)
			ToppingRepository toppingRepo;
			Topping topping;
			cin >> topping;
			toppingRepo.storeTopping(topping);
			cout << topping;
			break;
		}
		else if (registration == "price" || registration == "k") {
			//TODO: get the total price of an order
			break;
		} 
		else if (registration == "delivery" || registration == "d") {
			DeliveryUI deliveryUI;
			deliveryUI.deliveryMenu();
			break;
		}
		else if (registration == "other" || registration == "o") {
			SideOrder sideOrder;
			cout << sideOrder;
			break;
		}
		else if (registration == "quit" || registration == "q") {
			break;
		}
		cin.clear();
		cin.sync();
	}
}