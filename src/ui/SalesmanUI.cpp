#include "SalesmanUI.h"
#include "DeliveryUI.h"
#include "Order.h"
#include "SalesmanService.h"
#include <stdlib.h>
#include <iomanip> // setw

SalesmanUI::SalesmanUI()
{

}

void SalesmanUI::salesmanMenu() {
	string option;
	char input;
	while (true) {
		printMenu({ "Register an order", "Go back" });
		cout << endl;
		cout << "Press 'q' to quit.\nWhat would you like to do? "; 

		cin >> input;
		cin.ignore();

		system("CLS");

		switch (input) {
		case '1':
			makeNewOrder();
			break;
		case '2':
			return;
		case 'q':
		case 'Q':
			exit(1);
		}
	}
}
//Let the user pick from menu
void SalesmanUI::makeNewOrder()
{
	Order order;
	SalesmanService service;
	bool pizzaFromMenu = false;
	char input;
	int nrOfOrder = 1;
	
	selectLocation(order, input);

	while (true) {
		try
		{
			Pizza pizza;
			cout << "Order number " << nrOfOrder << "." << endl;
			// Asks the user if he wants to select a pizza from the menu
			selectFromMenu(pizzaFromMenu, input);

			selectCrust(pizza, input);
			selectSize(pizza, input);
			if (!pizzaFromMenu) {
				selectToppings(pizza, input);
			}
			// Append the pizza to the order
			service.appendToOrder(order, pizza);
			// Ask user if he wants any sides (can have multiple sides)
			selectSides(order, input);
			// Asks the user if he wants to add a comment
			addComment(order, input);
			// Asks the user if he wants to add another order
			if (!addAnotherOrder(input)) {
				showTotalOrder(order);
				system("pause");

				service.registerNewOrder(order);
				break;
			}
			system("CLS");
			nrOfOrder++;
		}
		catch (FailedOpenFile) {
			cout << "Failed to open a critical file...";
			break;
		}
	}
}

void SalesmanUI::pickFromMenu() {
	system("CLS");
	vector <Offer> offers = service.getItems<Offer>();
	cout <<"\n\t\tPIZZA MENU!" << endl;
	for (size_t i = 0; i < offers.size(); i++) {
		cout << endl;
		cout << "Pizzan nr." << i + 1 << ": " << endl;
		cout << offers.at(i);
		cout << "Toppings: ";
		for (size_t j = 0; j < offers.at(i).getOrder().getPizzas().size(); j++) {
			cout << offers.at(i).getOrder().getPizzas().at(j) << endl;
		}
	}
	cout << "Which pizza would you like?\nInput: ";
	char input;
	cin >> input;
	int inputInInt = (int)input - 49;
}

void SalesmanUI::selectLocation(Order& order, char & input)
{
	cout << "Welcome! Please pick a Pizza location from one of the following:" << endl;
	vector<Location> locations = service.getItems<Location>();
	for (size_t i = 0; i < locations.size(); i++) {
		cout << i + 1 << ": " << locations.at(i).getAddress() << endl;
	}
	cout << "Input: ";
	cin >> input;
	order.setLocation(locations.at((int)input - 49));
}

void SalesmanUI::selectFromMenu(bool& pizzaFromMenu, char & input)
{
	cout << "Would you like to pick from the menu (y/n)? ";
	cin >> input;
	if (tolower(input) == 'y') {
		pickFromMenu();
		pizzaFromMenu = true;
	}
	system("CLS");
}

void SalesmanUI::selectCrust(Pizza& pizza, char& input)
{
	vector<PizzaCrust> crusts = service.getItems<PizzaCrust>();
	cout << "Here are the crusts you can choose from:" << endl;
	printMenu(makeStringVector(crusts));
	cout << "Please choose one of them. \nInput: ";
	cin >> input;
	pizza.setCrust(crusts.at((int)input - 49));
	system("CLS");
}

void SalesmanUI::selectSize(Pizza & pizza, char& input)
{
	vector<PizzaSize> sizes = service.getItems<PizzaSize>();
	cout << "Here are the sizes you can choose from:" << endl;
	printMenu(makeStringVectorFromPizzaSize(sizes));
	cout << "Please choose one of them. \nInput: ";
	cin >> input;
	pizza.setPizzaSize(sizes.at((int)input - 49));
	system("CLS");
}

void SalesmanUI::selectToppings(Pizza & pizza, char& input)
{
	vector<Topping> toppings = service.getItems<Topping>();
	while (true)
	{
		cout << "Here are the toppings you can choose from:" << endl;
		printMenu(makeStringVector(toppings));
		cout << "How many toppings would you like? ";
		cout << "\nPlease enter 0 if you wish to have no toppings.\nInput: ";
		char numberOfToppings;
		cin >> numberOfToppings;
		int numberOfToppingsInt = (int)numberOfToppings - 48;
		for (int i = 0; i < numberOfToppingsInt; i++) {
			cout << "Topping number " << i + 1 << " is: ";
			cin >> input;
			if ((int)input - 48 == (toppings.size() + 1)) {
				break;
			}
			pizza.addToppings(toppings.at((int)input - 49));
		}
		break;
	}
	system("CLS");
}

void SalesmanUI::selectSides(Order & order, char & input)
{
	cout << endl << "Would you like any sides with your order? Y/N (yes/no): ";
	cin >> input;
	while (true)
	{
		if (toupper(input) == 'Y') {
			cout << "Here are side orders you can choose from: " << endl;
			vector<SideOrder> sideOrder = service.getItems<SideOrder>();
			for (size_t i = 0; i < sideOrder.size(); i++)
			{
				cout << i + 1 << ": " << sideOrder.at(i).getName() << " \t" << sideOrder.at(i).getPrice() << " kr.-" << endl;
			}
			cout << "Please choose one of them. \nInput: ";
			cin >> input;

			//Set the selected side order in service
			int index = (int)input - 49;
			service.appendToOrder(order, sideOrder.at(index));
		}
		else {
			break;
		}

		cout << "Would you like any more sides with your order? Y/N (yes/no): ";
		cin >> input;
	}
}

void SalesmanUI::addComment(Order & order, char & input)
{
	string comment = "None";
	cout << "Would you like to add a comment (y/n)? ";
	cin >> input;
	if (tolower(input) == 'y') {
		cout << "Comment: ";
		getInput(comment);
	}
	service.setComments(order, comment);
}

bool SalesmanUI::addAnotherOrder(char & input)
{
	cout << "Would you like to add another order to this?" << endl;
	cout << "Input (y/n): ";
	cin >> input;
	system("CLS");
	if (tolower(input) != 'y') {
		return false;
	}
	return true;
}

void SalesmanUI::showTotalOrder(Order & order)
{
	try 
	{
		if (service.validateOrder(order))
		{
			Pizza tempPizza;
			for (size_t i = 0; i < order.getPizzas().size(); i++) {
				tempPizza = order.getPizzas().at(i);
				cout << "Order nr. " << (i + 1) << ": " << endl;
				cout << "\t    Size: " << tempPizza.getPizzaSize().getName() << "  \t+" << (tempPizza.getPizzaSize().getPriceMod() - 1)*100 << " %" << endl;
				cout << "\t   Crust: " << tempPizza.getCrust().getName() << "  \t" << tempPizza.getCrust().getPrice() << " kr.-" << endl;
				cout << "\tToppings: " << endl;
				vector<Topping> tempTopping = tempPizza.getToppings();
				for (size_t j = 0; j < tempTopping.size(); j++) {
					cout << "\t\t  " << tempTopping.at(j).getName() << "   \t" << tempTopping.at(j).getPrice() << " kr.-" << endl;
				}
				cout << "\t  Sides: " << endl;
				vector<SideOrder> tempSides = order.getSides();
				for (size_t j = 0; j < tempSides.size(); j++) {
					cout << "\t\t  " << tempSides.at(j).getName() << "   \t" << tempSides.at(j).getPrice() << " kr.-" << endl;
				}
				cout << "\tComment: " << endl;
				cout << "\t\t  " << order.getComment() << endl;

			}
			cout << endl;
			cout << "---------- TOTAL ----------" << endl;
			cout << "\t   " << service.getPriceOfOrder(order) << "kr.-" << endl;
			cout << "---------------------------" << endl;
		}
	}
	catch (InvalidOrder) {
		cout << "Order is not valid..." << endl;
	}
}

vector<string> SalesmanUI::makeStringVectorFromPizzaSize(vector<PizzaSize> pizzaSizeVector)
{
	vector<string> returnVector;
	
	string tempString;
	string convertionString;
	for(size_t i = 0; i < pizzaSizeVector.size(); i++)
	{
		tempString = pizzaSizeVector.at(i).getName();
		tempString += " | ";
		convertionString = to_string((pizzaSizeVector.at(i).getPriceMod()-1) * 100);
		// Remove trailing 0's
		convertionString.erase(convertionString.find_last_not_of('0') + 1, string::npos);
		// If the last character is a dot, remove it
		if (convertionString[convertionString.size() - 1] == '.') {
			convertionString.erase(convertionString.find_last_not_of('.') + 1, string::npos);
		}
		tempString += convertionString;
		tempString += " %";

		returnVector.push_back(tempString);
	}

	return returnVector;
}
