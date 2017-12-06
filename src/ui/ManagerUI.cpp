#include "ManagerUI.h"
#include "../model/Topping.h"
#include "../data/Data.h"
#include "../model/SideOrder.h"
#include "DeliveryUI.h"
#include "Menu.h"
//For clearing the screen
#include <stdlib.h>

void ManagerUI::managerMenu() {
	char input = ' ';
	bool ignore = true;
	Menu menu;
	while (true) {
		system("CLS");
		cout << menu.printMenu({ "Pizza", "Toppings", "Price", "Delivery", "Other", "Go Back" }) << endl;
		cout << "Press 'q' to quit.\nWhat would you like to register? ";
		//not sure if needed anymore, check
		if (ignore) {
			cin.ignore();
		}
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
			toppings();
			break;
		}
		case '3':
		{
			//TODO: get the total price of an order
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
			break;
		case 'q':
		case 'Q':
			exit(1);
		default:
			cout << "Not a valid option." << endl;
		}
	}
}


//TODO: FIX
void ManagerUI::toppings() {
	int numberOfToppings;
	Data toppingRepo;
	Topping topping;
	char input;
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

		else if (inputInInt < 0 || toppings.size() <= inputInInt) {
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
