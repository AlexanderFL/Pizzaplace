#include "DeliveryUI.h"

//TODO: Fix home address! 

DeliveryUI::DeliveryUI()
{
	ignore = true;
}

DeliveryUI::~DeliveryUI()
{
}

void DeliveryUI::setIgnore(bool ignore) {
	this-> ignore = ignore;
}

void DeliveryUI::deliveryMenu() {
	string homeAddress;
	//TODO: Kalla í fallið numberOfOrders þegar það er tilbúið og setja útkomuna í int numberOfOrders 
	int numberOfOrders = 0;
	char input;
	while (true) {
		cout << "Where would you like it delivered? ";
		//Using the bool ignore, so that it doesn't accidently ignore an input
		if (ignore) {
			cin.ignore();
		}
		else {
			ignore = true;
		}
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
	//TODO: Call a function to delete an Order, if orders  >= 1.
}
