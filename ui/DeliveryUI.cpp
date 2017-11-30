#include "DeliveryUI.h"


DeliveryUI::DeliveryUI()
{
}


DeliveryUI::~DeliveryUI()
{
}

void DeliveryUI::deliveryMenu() {
	string homeAddress;
	//Nota annað notafjölda orders hér, setti numberOfOrders = 0 bara til að skrifa fallið upp
	int numberOfOrders = 0;
	char input;
	while (true) {
		cout << "Where would you like it delivered? ";
		cin.ignore();
		getline(cin, homeAddress);
		cout << "Your home address is " << homeAddress << ". Is this correct? (y/n): ";
		cin >> input;
		if (tolower(input) == 'y') {
			break;
		}
		//To be able to use getline again without error
		cin.clear();
		cin.sync();
	}
	cout << "This home address has " << numberOfOrders << " order";

	if (numberOfOrders > 1) {
		cout << "s.\nYour orders are: ";
		//Add orders here
	}
	else if (numberOfOrders == 1) {
		cout << "Your order is:";
	}
	else {
		cout << "s.";
	}
	cout << "\nWould you like to add an Order?(y/n): ";
	cin >> input;
	if (tolower(input) == 'y') {
		//call the function to add an order
	}
	//Also add if they want to delete an Order (only if they have 1 or more orders).
	
}
