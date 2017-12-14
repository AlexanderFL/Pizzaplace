#include "SalesmanUI.h"
#include "DeliveryUI.h"
#include "Order.h"
#include "SalesmanService.h"
#include <stdlib.h>

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
	system("CLS");
	while (true) {
		try
		{
			Pizza pizza;
			cout << "Order number " << nrOfOrder << "." << endl;
			// Asks the user if he wants to select a pizza from the menu
			selectFromMenu(order, pizzaFromMenu, input);

			if (!pizzaFromMenu) {
				selectCrust(pizza, input);
				selectSize(pizza, input);
				selectToppings(pizza, input);
				
				// Append the pizza to the order
				service.appendToOrder(order, pizza);
			}
			// Ask user if he wants any sides (can have multiple sides)
			selectSides(order, input);
			// Asks the user if he wants to add a comment
			addComment(order, input);
			// Ask for delivery method
			selectDeliveryMethod(order, input);
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
	system("CLS");
}

void SalesmanUI::pickFromMenu(Order& order, char& input) {
	system("CLS");
	vector <Offer> offers = service.getItems<Offer>();
	cout <<"\n\t\tPIZZA MENU!" << endl;

	for (size_t i = 0; i < offers.size(); i++) {
		cout << endl;
		cout << "-------------------------" << endl << endl;
		cout << "Order nr." << i + 1 << ": ";
		cout << offers.at(i).getName() << endl;
		
		vector<Pizza> tempPizza = offers.at(i).getOrder().getPizzas();
		for (size_t j = 0; j < tempPizza.size(); j++) {
			cout << "Pizza nr." << j+1 << endl; 
			cout << "   Crust: " << tempPizza.at(j).getCrust().getName() << "  \t" << tempPizza.at(j).getCrust().getPrice() << " kr.-" << endl;
			cout << "    Size: " << tempPizza.at(j).getPizzaSize().getName() << " \t+" << (tempPizza.at(j).getPizzaSize().getPriceMod()-1)*100 << " %" << endl;
			cout << "Toppings: " << endl;
			vector<Topping> tempToppings = tempPizza.at(j).getToppings();
			for (size_t k = 0; k < tempToppings.size(); k++) {
				cout << "\t  " << tempToppings.at(k).getName() << "    \t" << tempToppings.at(k).getPrice() << " kr.-" << endl;
			}
		}
		cout << "TOTAL: " << service.getPriceOfOrder(offers.at(i).getOrder()) << " kr.- " << endl;
	}
	cout << endl;
	cout << "Which order would you like?\nInput order number: ";
	cin >> input;
	int inputInInt = (int)input - 49;
	
	order = offers.at(inputInInt).getOrder();
}

void SalesmanUI::selectLocation(Order& order, char & input)
{
	vector<Location> locations = service.getItems<Location>();
	vector<string> stringifyLocations;
	for (size_t i = 0; i < locations.size(); i++) {
		stringifyLocations.push_back(locations.at(i).getAddress());
	}
	printMenu({stringifyLocations}, "Please A Select Location");
	getInput("Input", input);
	order.setLocation(locations.at((int)input - 49));
}

void SalesmanUI::selectFromMenu(Order& order, bool& pizzaFromMenu, char & input)
{
	printMenu({"Yes | (Y)", "No | (N)"}, "Would you like to pick from the menu?");
	getInput("Input", input);
	if (tolower(input) == 'y') {
		pickFromMenu(order, input);
		pizzaFromMenu = true;
	}
	clear();
}

void SalesmanUI::selectCrust(Pizza& pizza, char& input)
{
	vector<PizzaCrust> crusts = service.getItems<PizzaCrust>();
	printMenu(makeStringVector(crusts), "Select the Pizza Crust");
	while (true) {
		try
		{
			getInput("Input", input);
			service.validInput(input, crusts);
			pizza.setCrust(crusts.at((int)input - 49));
			clear();
			break;
		}
		catch (InvalidInput ex) {
			printMessage(ex.getMessage());
		}
	}
}

void SalesmanUI::selectSize(Pizza & pizza, char& input)
{
	vector<PizzaSize> sizes = service.getItems<PizzaSize>();
	printMenu(makeStringVectorFromPizzaSize(sizes), "Select the Pizza Size");
	while (true)
	{
		try 
		{
			getInput("Input", input);
			pizza.setPizzaSize(sizes.at((int)input - 49));
			service.validInput(input, sizes);
			clear();
			break;
		}
		catch (InvalidInput ex)
		{
			printMessage(ex.getMessage());
		}
	}
}

void SalesmanUI::selectToppings(Pizza & pizza, char& input)
{
	vector<Topping> toppings = service.getItems<Topping>();
	while (true)
	{
		printMenu(makeStringVector(toppings), "Select the Toppings");
		try
		{
			getInput("Please enter the number of toppings", input);
		}
		int numberOfToppingsInt = (int)input - 48;
		for (int i = 0; i < numberOfToppingsInt; i++) {
			string inputString = "Select topping nr " + to_string(i+1);
			// Keeps asking the user for the next topping if he enters a invalid input
			while (true)
			{
				try
				{
					getInput(inputString, input);
					pizza.addToppings(toppings.at((int)input - 49));
					break;
				}
				catch (InvalidInput ex) {
					printMessage(ex.getMessage());
				}
			}
		}
		break;
	}
	clear();
}

void SalesmanUI::selectSides(Order & order, char & input)
{
	printMenu({ "Yes | (Y)", "No | (N)" }, "Would you like any sides with your order?");
	getInput("Input", input);
	clear();
	while (true)
	{
		if (toupper(input) == 'Y') {
			vector<SideOrder> sideOrder = service.getItems<SideOrder>();
			vector<string> stringifySideOrder;
			string tempString;
			for (size_t i = 0; i < sideOrder.size(); i++)
			{
				tempString = sideOrder.at(i).getName();
				tempString += " | ";
				tempString += to_string(sideOrder.at(i).getPrice()) + " kr.-";
				stringifySideOrder.push_back(tempString);
			}
			printMenu(stringifySideOrder, "Please choose a side order");
			getInput("Input", input);

			//Set the selected side order in service
			int index = (int)input - 49;
			service.appendToOrder(order, sideOrder.at(index));

			clear();
			printMenu({ "Yes | (Y)", "No | (N)" }, "Would you like any more sides with your order?");
			getInput("Input", input);
		}
		else {
			break;
		}
	}
	clear();
}

void SalesmanUI::addComment(Order & order, char & input)
{
	string comment = "None";
	printMenu({ "Yes | (Y)", "No | (N)" }, "Would you like to add a comment?");
	getInput("Input", input);
	if (tolower(input) == 'y') {
		getInput("Comment", comment);
	}
	service.setComments(order, comment);
	clear();
}

void SalesmanUI::selectDeliveryMethod(Order & order, char & input)
{
	while (true)
	{
		printMenu({"Pickup", "Send"}, "How would you like your pizza delivered?");
		getInput("Input", input);
		if (input == '1') {
			service.setOrderToPickUp(order);
			break;
		}
		else if (input == '2') {
			service.setOrderToDelivery(order);
			break;
		}
		else {
			clear();
			printMessage("Input not valid");
		}
	}
	clear();
}

bool SalesmanUI::addAnotherOrder(char & input)
{
	printMenu({ "Yes | (Y)", "No | (N)" }, "Would you like to add another order to this?");
	getInput("Input", input);
	clear();
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
				
			for (size_t i = 0; i < order.getPizzas().size(); i++) 
			{
				//string title = "Order nr. " + to_string(i + 1);
				//printMenu({"Test for", "a new", "feature"}, title, true);

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

/*
	Converting the PizzaSize vector to a string vector by 
	displaying the name and price modifier in a single string
*/
vector<string> SalesmanUI::makeStringVectorFromPizzaSize(vector<PizzaSize> pizzaSizeVector)
{
	vector<string> returnVector;
	
	string tempString;
	string convertionString;
	for(size_t i = 0; i < pizzaSizeVector.size(); i++)
	{
		tempString = pizzaSizeVector.at(i).getName();
		tempString += " | +";
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
