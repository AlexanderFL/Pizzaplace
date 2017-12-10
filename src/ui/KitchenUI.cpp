#include "KitchenUI.h"

KitchenUI::KitchenUI()
{

}

//TODO: Only allow certain workplaces and let the user pick from that
void KitchenUI::kitchenMenu() {
	char workplace;
	char input;
	Data locationRepo;
	vector<Location> locations = service.getLocations();
	Location location;
	while (true) {
		try {
 			vector<Location> locations = service.getLocations();
			cout << "Choose the location of your workplace" << endl;
			for (size_t i = 0; i < locations.size(); ++i) {
				cout << i + 1 << ": " << locations.at(i).getAddress() << endl;
			}
			cout << "Input: ";
			cin >> input;
			try {
				vector<Pizza> pizzas = service.getPizzas(locations.at((int)input - 49));
				for (size_t i = 0; i < pizzas.size(); ++i) {
					cout << i + 1 << ": " << pizzas.at(i).getPhase() << endl;
				}
				cout << "Input: ";
				cin >> input;
				try {
					cout << pizzas.at((int)input - 49) << endl;
					cout << "Set as Baking" << endl;
					cout << "Set as Ready" << endl;
					cout << "Back" << endl;
					cout << "Input: ";
					cin >> input;
				}
				catch (out_of_range) {
					cout << "Invalid index" << endl;
				}
			}
			catch (out_of_range) {
				cout << "Invalid index" << endl;
			}
			catch (EmptyVector) {
				cout << "No pizzas av" << endl;
			}
			catch (FailedOpenFile) {
				cout << "Failed open file 2" << endl;
			}
		}
		catch (EmptyVector) {
			cout << "No locations av" << endl;
		}
		catch (FailedOpenFile) {
			cout << "Failed opne file 1" << endl;
		}

		cout << "Where do you work? ";
		cin.ignore();
		cin >> workplace;
		int workplaceInInt = workplace - 49;
		cout << "You work at " << locations.at(workplaceInInt).getAddress() << ". Is this correct? (y/n): ";
		cin >> input;
		if (tolower(input) == 'y') {
			break;
		}

		//To be able to use getline again without error
		cin.clear();
		cin.sync();
	}
}