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
		//not sure if needed anymore, check
		if (ignore) {
			cin.ignore();
		}

		getline(cin, registration);
		//String size set to lower
		transform(registration.begin(), registration.end(), registration.begin(), ::tolower);

		if (registration == "pizza" || registration == "1") {
			cout << "a";
		}

		else if (registration == "toppings" || registration == "2") {
			char input;
			int numberOfToppings;
			Data toppingRepo;
			Topping topping;
			cout << "What would you like to do? \n"
				<< "1. Add a topping.\n"
				<< "2. Delete a topping.\n"
				<< "3. See all the toppings you have so far.\n"
				<< "Input: ";
			cin >> input;
			//Add a topping
			if (input == '1') {
				//TODO: fix and add (also be able to delete a toping)
				cout << "How many toppings would you like to add? ";
				cin >> numberOfToppings;
				cout << "What would you like as a topping? " << endl;

				for (int i = 0; i < numberOfToppings; ++i) {
					cout << "Topping number " << i + 1 << ": ";
					cin >> topping;
					toppingRepo.WriteToFile(topping);
				}
			}
			//Delete a topping
			else if (input == '2') {
				vector <Topping> toppings = toppingRepo.RetrieveAllFromFile<Topping>();
				cout << "Here are the toppings you have so far: " << endl;
				for (unsigned int i = 0; i < toppings.size(); i++) {
					cout << i + 1 << ": " <<  toppings.at(i) << endl;
				}
				cout << "What topping would you like to delete. Please input a number or 'q' to quit." << endl;
				cout << "Input: ";
				cin >> input;
				int inputInInt = (int)input - 49;
				if (tolower(input) == 'q') {
					break;
				}
				else if (inputInInt < 0 || toppings.size() <= inputInInt)  {
					cout << "Invalid input." << endl;
				}
				else toppingRepo.RemoveFromFileAtIndex<Topping>(inputInInt);
			}
			else if (input == '3') {
				vector <Topping> toppings = toppingRepo.RetrieveAllFromFile<Topping>();
				cout << "Here are the toppings you have so far: " << endl;
				for (unsigned int i = 0; i < toppings.size(); i++) {
					cout << i + 1 << ": " << toppings.at(i) << endl;
				}
			}
			else {
				cout << "Invalid input." << endl;
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
		//cin.clear();
		//cin.sync();
	}
}