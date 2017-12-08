#include <iostream>

#include "Data.h"

using namespace std;
#include "MainUI.h"
//#include <cstdlib>
//#include <time.h>

Data repo;

void addTopping();
void addCrust();
void addSize();
void addSide();
void addLocation();
void addOrder();

/*long lrand()
{
	if (sizeof(int) < sizeof(unsigned long))
		return (static_cast<unsigned long>(rand()) << (sizeof(unsigned int) * 8)) |
		rand();

	return rand();
}*/
/*unsigned long long ullRandGen() {
	unsigned long long n = abs(rand());
	return (n << (sizeof(int) * 8)) | abs(rand());
}*/

int main()
{
	MainUI mainUI;
	mainUI.startUI();
	string input;
	do {
		cout << "1. Add topping" << endl;
		cout << "2. Add crust" << endl;
		cout << "3. Add size" << endl;
		cout << "4. Add side" << endl;
		cout << "5. Add location" << endl;
		cout << "6. Create order" << endl;
		cout << "q. Quit" << endl;
		cout << "Input: ";
		cin >> input;
		if (input == "1") {
			addTopping();
		}
		else if (input == "2") {
			addCrust();
		}
		else if (input == "3") {
			addSize();
		}
		else if (input == "4") {
			addSide();
		}
		else if (input == "5") {
			addLocation();
		}
		else if (input == "6") {
			addOrder();
		}
	} while (input != "q");
	return 0;
}

void addTopping() {
	cout << "Creating a new Topping" << endl;
	cout << "Name: ";
	string name;
	cin >> name;
	cout << "Price: ";
	double price;
	cin >> price;
	repo.WriteToFile(Topping(name, price));
}

void addCrust() {
	cout << "Creating a new Crust" << endl;
	cout << "Name: ";
	string name;
	cin >> name;
	cout << "Price: ";
	double price;
	cin >> price;
	repo.WriteToFile(PizzaCrust(name, price));
}

void addSize() {
	cout << "Creating a new Size" << endl;
	cout << "Name: ";
	string name;
	cin >> name;
	cout << "Mod: ";
	double mod;
	cin >> mod;
	repo.WriteToFile(PizzaSize(name, mod));
}

void addSide() {
	cout << "Creating a new Side" << endl;
	cout << "Name: ";
	string name;
	cin >> name;
	cout << "Price: ";
	double price;
	cin >> price;
	repo.WriteToFile(SideOrder(name, price));
}

void addLocation() {
	cout << "Creating a new Location" << endl;
	cout << "Name: ";
	string name;
	cin >> name;
	repo.WriteToFile(Location(name));
}

void addOrder() {
	string input;
	vector<Topping> toppings;
	vector<SideOrder> sides;
	vector<Pizza> pizzas;
	PizzaCrust crust;
	PizzaSize size;
	Location location;
	do {
		cout << "1. Add topping" << endl;
		cout << "2. Choose crust" << endl;
		cout << "3. Choose size" << endl;
		cout << "4. Add side" << endl;
		cout << "5. Choose location" << endl;
		cout << "6. Complete" << endl;
		cout << "q. Quit" << endl;
		cout << "Input: ";
		cin >> input;
		if (input == "1") {
			vector<Topping> tops = repo.RetrieveAllFromFile<Topping>();
			cout << "Choose a topping" << endl;
			for (int i = 0; i < tops.size(); ++i) {
				cout << i << " " << tops.at(i) << endl;
			}
			int inp;
			cin >> inp;
			toppings.push_back(tops.at(inp));
		}
		else if (input == "2") {
			vector<PizzaCrust> crusts = repo.RetrieveAllFromFile<PizzaCrust>();
			cout << "Choose a crust" << endl;
			for (int i = 0; i < crusts.size(); ++i) {
				cout << i << " " << crusts.at(i) << endl;
			}
			int inp;
			cin >> inp;
			crust = crusts.at(inp);
		}
		else if (input == "3") {
			vector<PizzaSize> sizes = repo.RetrieveAllFromFile<PizzaSize>();
			cout << "Choose a crust" << endl;
			for (int i = 0; i < sizes.size(); ++i) {
				cout << i << " " << sizes.at(i) << endl;
			}
			int inp;
			cin >> inp;
			size = sizes.at(inp);
		}
		else if (input == "4") {
			vector<SideOrder> sds = repo.RetrieveAllFromFile<SideOrder>();
			cout << "Choose a topping" << endl;
			for (int i = 0; i < sds.size(); ++i) {
				cout << i << " " << sds.at(i) << endl;
			}
			int inp;
			cin >> inp;
			sides.push_back(sds.at(inp));
		}
		else if (input == "5") {
			vector<Location> locs = repo.RetrieveAllFromFile<Location>();
			cout << "Choose a location" << endl;
			for (int i = 0; i < locs.size(); ++i) {
				cout << i << " " << locs.at(i) << endl;
			}
			int inp;
			cin >> inp;
			location = locs.at(inp);
		}
		else if (input == "6") {
			string comment, address;
			cout << "Comment: ";
			cin >> comment;
			cout << "Address: ";
			cin >> address;
			pizzas.push_back(Pizza(toppings, crust, size));
			//repo.WriteToFile(Order(pizzas, sides, 0, 0, location, comment, address));
		}
	} while (input != "q");
}