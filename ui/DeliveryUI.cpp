#include "DeliveryUI.h"


DeliveryUI::DeliveryUI()
{
}


DeliveryUI::~DeliveryUI()
{
}

void DeliveryUI::deliveryMenu() {
	string homeAddress;
	int numberOfOrders = 0;
	char input;
	while (true) {
		cout << "Where would you like it delivered? ";
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
	if (numberOfOrders > 1) {
		cout << "ba;";
	}
	else if (numberOfOrders == 1) {
		cout << "d3";
	}
	else {
		cout << "hsdg";
	}
}
