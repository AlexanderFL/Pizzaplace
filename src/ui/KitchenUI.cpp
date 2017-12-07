#include "KitchenUI.h"

KitchenUI::KitchenUI()
{

}

//TODO: Only allow certain workplaces and let the user pick from that
void KitchenUI::kitchenMenu() {
	string workplace;
	char input;
	while (true) {
		cout << "Where do you work? ";
		cin.ignore();
		getline(cin, workplace);
		cout << "You work at " << workplace << ". Is this correct? (y/n): ";
		cin >> input;
		if (tolower(input) == 'y') {
			break;
		}

		//To be able to use getline again without error
		cin.clear();
		cin.sync();
	}
}