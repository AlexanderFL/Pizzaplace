#include <iostream>

#include "Data.h"

using namespace std;
#include "MainUI.h"

/*Data repo;

void addTopping();
void addCrust();
void addSize();
void addPizza();*/

int main()
{
	MainUI mainUI;
	mainUI.startUI();
	/*string input;
	do {
		cout << "1. Add topping" << endl;
		cout << "2. Add crust" << endl;
		cout << "3. Add size" << endl;
		cout << "4. Create pizza" << endl;
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
			addPizza();
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
	cout << "Creating a new size" << endl;
	cout << "Name: ";
	string name;
	cin >> name;
	cout << "Mod: ";
	double mod;
	cin >> mod;
	repo.WriteToFile(PizzaSize(name, mod));
}

void addPizza() {
	string input;
	vector<Topping> toppings;
	PizzaCrust crust;
	PizzaSize size;
	Pizza pizza;
	do {
		cout << "1. Add topping" << endl;
		cout << "2. Choose crust" << endl;
		cout << "3. Choose size" << endl;
		cout << "4. Complete" << endl;
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
			vector<Topping> crusts = repo.RetrieveAllFromFile<PizzaCrust>();
			cout << "Choose a crust" << endl;
			for (int i = 0; i < crusts.size(); ++i) {
				cout << i << " " << crusts.at(i) << endl;
			}
			int inp;
			cin >> inp;
			crust = crusts.at(inp);
		}
		else if (input == "3") {
			
		}
		else if (input == "4") {
			
		}
	} while (input != "q");*/
}