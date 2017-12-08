#include "ManagerUI.h"
#include "Topping.h"
#include "Data.h"
#include "SideOrder.h"
#include "DeliveryUI.h"
#include "Menu.h"
#include "Order.h"
#include "Location.h"
//For clearing the screen
#include <stdlib.h>


//TODO: Fix comment on the bottom and make this code more readable.

ManagerUI::ManagerUI() {
	char input = ' ';
}

void ManagerUI::managerMenu() {
	bool ignore = true;
	Menu menu;
	bool stillManager = true;
	while (stillManager) {
		//system("CLS");
		cout << menu.printMenu({ "Pizza", "Toppings", "Price", "Locations", "Other", "Go Back" }) << endl;
		cout << "Press 'q' to quit.\nWhat would you like to register? ";

		cin.ignore();
		cin >> input;
		system("CLS");

		switch (input)
		{
		case '1':
		{
			//Pizza
			break;
		}
		case '2':
		{
			//Toppings
			do{
			cout << menu.printMenu({ "Add a topping", "Delete a topping", "See all toppings", "Go Back" }) << endl;
			cout << "Input: ";
			cin >> input;
			system("CLS");
			validateToppingInput(input);
		} while (input != 52); //ascii - checking if input is 4 (go back)
			break;
		}


		case '3':
		{
			//Price
			//TODO: get the total price of an order
			//Data orderRepo;
			//vector<Order> order;
			//order = orderRepo.RetrieveAllFromFile<Order>();
			//Todo replace with service
			//cout << order.getTotalCost();
			//cout << "The total price of the order is: " << service.getOrderTotalCost(order) << " kr." << endl;
			break;
		}



		case '4':
		{
			bool stillOnLocation = true;
			while (stillOnLocation) {
				//Locations
				Data locationRepo;
				vector<Location> locations = service.getLocations();
				Location location;

				cout << menu.printMenu({ "Add a location", "Remove a location", "See all Locations", "Go Back" }) << endl;
				cout << "What would you like to do? ";
				cin >> input;
					switch (input) {
					case '1':
					{
						//Adding a location
						int numberOfLocations;
						cout << "How many locations would you like to add? ";
						cin >> numberOfLocations;
						cout << "Where would you like the locatins to be? " << endl;

						for (int i = 0; i < numberOfLocations; ++i) {
							cout << "location number " << i + 1 << ": ";
							cin >> location;
							service.addLocation(location);
						}
						break;
					}
					case '2':
					{
						//Delete a Location
						if (locations.size() != 0) {
							cout << "Here are the locations you have so far: " << endl;
							for (unsigned int i = 0; i < locations.size(); i++) {
								cout << i + 1 << ": " << locations.at(i).getAddress() << endl;
							}
							cout << "What location would you like to delete. Please input a number or 'q' to quit." << endl;
							cout << "Input: ";
							cin >> input;
							//Changing the input from char to int
							int inputInInt = (int)input - 49;
							if (tolower(input) == 'q') {
								exit(1);
							}
							service.deleteLocation(inputInInt);
						}
						else cout << "You have no locations so far." << endl;
						break;
					}

					case '3': {
						//See all locations
						if (locations.size() != 0) {
							cout << "Here are the locations you have so far: " << endl;
							for (unsigned int i = 0; i < locations.size(); i++) {
								cout << i + 1 << ": " << locations.at(i).getAddress() << endl;
							}
						}
						else cout << "You have no locations so far." << endl;
						system("PAUSE");
						break;
					}
					case '4':
						stillOnLocation = false;
				}
			}
		}



		case '5':
			//Other
			do{
			cout << menu.printMenu({ "Add a side order", "delete a side order",  "See all side orders", "Go Back" }) << endl;
			cout << "Input: ";
			cin >> input;
			system("CLS");
				validateOtherInput(input);
			} while (input != 52); //ascii - checking if input is 4 (go back)
			break;
		case '6':
			//Go back
			stillManager = false;
			break;
		case 'q':
		case 'Q':
			exit(1);
		default:
			cout << "Not a valid option." << endl;
		}
	}
}


/*
	Changing Toppings on Pizza
*/


void ManagerUI::validateToppingInput(char input) {
	//notar her toppingrepo, fix
	Data toppingRepo;
	vector <Topping> toppings;
	toppings = toppingRepo.RetrieveAllFromFile<Topping>();
	Topping topping;

	switch (input) {
	case '1': {
		//Adding a topping
		int numberOfToppings;
		cout << "How many toppings would you like to add? ";
		cin >> numberOfToppings;
		cout << "What would you like as a topping? " << endl;

		for (int i = 0; i < numberOfToppings; ++i) {
			cout << "Topping number " << i + 1 << ": ";
			cin >> topping;
			service.addTopping(topping);
		}
		break;
	}
	case '2': {
		//Delete a topping
		vector <Topping> toppings = toppingRepo.RetrieveAllFromFile<Topping>();
		if (toppings.size() != 0) {
			cout << "Here are the toppings you have so far: " << endl;
			for (unsigned int i = 0; i < toppings.size(); i++) {
				cout << i + 1 << ": " << toppings.at(i) << endl;
			}
			cout << "What topping would you like to delete. Please input a number or 'q' to quit." << endl;
			cout << "Input: ";
			cin >> input;
			//Changing the input from char to int
			int inputInInt = (int)input - 49;
			if (tolower(input) == 'q') {
				exit(1);
			}
			service.deleteTopping(inputInInt);
		}
		else cout << "You have no toppings so far." << endl;
		break;
		}
		case '3': {
			//See all toppings
			if (toppings.size() != 0) {
				cout << "Here are the toppings you have so far: " << endl;
				for (unsigned int i = 0; i < toppings.size(); i++) {
					cout << i + 1 << ": " << toppings.at(i) << endl;
				}
			}
			else cout << "You have no toppings so far." << endl;
			system("PAUSE");
			break;
		}
		case '4': {
			//Go back
			break;
		}
		default: {
			cout << "Invalid input." << endl;
			break;
		}
	}
}

/*
	Adding other products to purchase
*/

//TODO: fix managerservice for side order
void ManagerUI::validateOtherInput(char input) {
	Data sideOrderRepo;
	vector <SideOrder> sides;
	sides = sideOrderRepo.RetrieveAllFromFile<SideOrder>();
	SideOrder sideOrder;
	switch (input) {
		case '1': {
			//Add a side order
			int numberOfSides;
			cout << "How many side orders would you like to add? ";
			cin >> numberOfSides;
			cout << "What would you like as a side order? " << endl;

			for (int i = 0; i < numberOfSides; ++i) {
				cout << "Side number " << i + 1 << ": ";
				cin >> sideOrder;
				service.addSideOrder(sideOrder);
			}
			break;
		}
		case '2': {
			//delete a side order
			if (sides.size() != 0) {
				cout << "Here are the side orders you have so far: " << endl;
				for (unsigned int i = 0; i < sides.size(); i++) {
					cout << i + 1 << ": " << sides.at(i) << endl;
				}
				cout << "What topping would you like to delete. Please input a number or 'q' to quit." << endl;
				cout << "Input: ";
				cin >> input;
				//Changing the input from char to int
				int inputInInt = (int)input - 49;
				if (tolower(input) == 'q') {
					exit(1);
				}
				service.deleteSideOrder(inputInInt);
			}
			else cout << "You have no side orders so far." << endl;
			break;
		}
		case '3': {
			//See all side orders
			if (sides.size() != 0) {
				cout << "Here are the side orders you have so far: " << endl;
				for (unsigned int i = 0; i < sides.size(); i++) {
					cout << i + 1 << ": " << sides.at(i) << endl;
				}
			}
			else cout << "You have no side orders so far." << endl;
			break;
		}
		case '4': {
			//go back
			break;
		}
		default:
			cout << "Invalid input." << endl;
			break;
		}
}




/*
void ManagerUI::addTopping() {
	int numberOfToppings;
	Topping topping;
	cout << "How many toppings would you like to add? ";
	cin >> numberOfToppings;
	cout << "What would you like as a topping? " << endl;

	for (int i = 0; i < numberOfToppings; ++i) {
		cout << "Topping number " << i + 1 << ": ";
		cin >> topping;
		service.addTopping(topping);
	}
}

void ManagerUI::deleteTopping() {
	Data toppingRepo;
	cout << "What topping would you like to delete. Please input a number or 'q' to quit." << endl;
	cout << "Input: ";
	cin >> input;
	//Changing the input from char to int
	int inputInInt = (int)input - 49;
	if (tolower(input) == 'q') {
		exit(1);
	}

	else if (inputInInt < 0 || toppings.size() <= inputInInt) {
		cout << "Invalid input." << endl;
	}
	else toppingRepo.RemoveFromFileAtIndex<Topping>(inputInInt);
}

void ManagerUI::seeAllToppings() {
	cout << "Here are the toppings you have so far: " << endl;
	for (unsigned int i = 0; i < toppings.size(); i++) {
		cout << i + 1 << ": " << toppings.at(i) << endl;
	}
}
*/