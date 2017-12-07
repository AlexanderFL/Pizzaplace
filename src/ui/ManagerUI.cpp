#include "ManagerUI.h"
#include "Topping.h"
#include "Data.h"
#include "SideOrder.h"
#include "DeliveryUI.h"
#include "Menu.h"
#include "Order.h"
//For clearing the screen
#include <stdlib.h>

ManagerUI::ManagerUI() {
	char input = ' ';
}

void ManagerUI::managerMenu() {
	bool ignore = true;
	Menu menu;
	bool stillManager = true;
	while (stillManager) {
		//system("CLS");
		cout << menu.printMenu({ "Pizza", "Toppings", "Price", "Delivery", "Other", "Go Back" }) << endl;
		cout << "Press 'q' to quit.\nWhat would you like to register? ";

		cin.ignore();
		cin >> input;
		system("CLS");

		switch (input)
		{
		case '1':
		{
			break;
		}
		case '2':
		{
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
			bool ignore = false;
			DeliveryUI deliveryUI;
			deliveryUI.setIgnore(ignore);
			deliveryUI.deliveryMenu();
			break;
		}
		case '5':
			//TODO: add other options for manager
			do{
			cout << menu.printMenu({ "Add a side order", "delete a side order", "Go Back" }) << endl;
			cout << "Input: ";
			cin >> input;
			system("CLS");
				validateOtherInput(input);
			} while (input != 51); //ascii - checking if input is 3 (go back)
			break;
		case '6':
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
		break;
	}
	case '3': {
		//See all toppings
		cout << "Here are the toppings you have so far: " << endl;
		for (unsigned int i = 0; i < toppings.size(); i++) {
			cout << i + 1 << ": " << toppings.at(i) << endl;
		}
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

void ManagerUI::validateOtherInput(char input) {
	switch (input) {
		case '1': {
			//Add a side order
			break;
		}
		case '2': {
			//delete a side order
			break;
		}
		case '3': {
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