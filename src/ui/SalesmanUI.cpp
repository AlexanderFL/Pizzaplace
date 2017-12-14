#include "SalesmanUI.h"
#include "DeliveryUI.h"
#include "Order.h"
#include "SalesmanService.h"
#include <stdlib.h>

SalesmanUI::SalesmanUI()
{
	_pizzaNumber = 1;
}

void SalesmanUI::salesmanMenu() {
	string option;
	char input;
	while (true) {
		printMenu({ "Register an order", "Go back" });
		std::cout << endl;
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
			// Prompt the user to make a new order by either
			// selecting from menu or making his own pizza
			newOrderStart(order, pizzaFromMenu, input);

			if (!pizzaFromMenu) {

				makeYourOwnMenu(order, input);

				//selectCrust(pizza, input);
				//selectSize(pizza, input);
				//selectToppings(pizza, input);
				
				// Append the pizza to the order
				//service.appendToOrder(order, pizza);
			}
			// Ask user if he wants any sides (can have multiple sides)
			// selectSides(order, input);
			// Asks the user if he wants to add a comment
			// addComment(order);
			// Ask for delivery method
			// selectDeliveryMethod(order, input);
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

void SalesmanUI::makeYourOwnMenu(Order& order, char& input)
{
	Pizza newPizza;
	printMenu(
		{"Select crust", "Select size", "Select toppings", "Add sides", "Select delivery method", "Add comment", "Finish"}, 
		"Make your own pizza!"
	);
	catchCharInput(input, 7, 1);
	clear();

	switch (input)
	{
	case '1':
		selectCrust(newPizza, input);
	case '2':
		selectSize(newPizza, input);
	case '3':
		selectToppings(newPizza, input);
	case '4':
		selectSides(order, input);
	case '5':
		selectDeliveryMethod(order, input);
	case '6':
		addComment(order);
	case '7':
		break;
	default:
		return;
	}
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

void SalesmanUI::newOrderStart(Order& order, bool& pizzaFromMenu, char & input)
{
	printMenu({"Select from menu", "Make your own pizza!"}, "Make a new order");

	catchCharInput(input, 2, 1);

	if (tolower(input) == '1') {
		pickFromMenu(order, input);
		pizzaFromMenu = true;
	}
	clear();
}

void SalesmanUI::selectCrust(Pizza& pizza, char& input)
{
	vector<PizzaCrust> crusts = service.getItems<PizzaCrust>();
	printMenu(makeStringVector(crusts), "Select the Pizza Crust");
	catchCharInput(input, crusts.size());
	pizza.setCrust(crusts.at((int)input - 49));
	clear();
}

void SalesmanUI::selectSize(Pizza & pizza, char& input)
{
	vector<PizzaSize> sizes = service.getItems<PizzaSize>();
	printMenu(makeStringVectorFromPizzaSize(sizes), "Select the Pizza Size");

	catchCharInput(input, sizes.size());
	pizza.setPizzaSize(sizes.at((int)input - 49));
	clear();
}

void SalesmanUI::selectToppings(Pizza & pizza, char& input)
{
	vector<Topping> toppings = service.getItems<Topping>();
	while (true)
	{
		printMenu(makeStringVector(toppings), "Select the Toppings");
		
		// Cannot have more than two of each topping so multiply all toppings by 2
		catchCharInput(input, toppings.size() * 2, 0, "Please enter the number of toppings");
		int numberOfToppingsInt = (int)input - 48;

		for (int i = 0; i < numberOfToppingsInt; i++) {
			string inputString = "Select topping nr " + to_string(i+1);
			catchCharInput(input, pizza.getToppings().size(), 0, inputString);
			pizza.addToppings(toppings.at((int)input - 49));
		}
		break;
	}
	clear();
}

void SalesmanUI::selectSides(Order& order, char& input)
{
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
	catchCharInput(input, sideOrder.size());

	//Set the selected side order in service
	int index = (int)input - 49;
	service.appendToOrder(order, sideOrder.at(index));

	clear();
}

void SalesmanUI::addComment(Order & order)
{
	string comment = "None";
	getInput("Insert comment: ", comment);
	service.setComments(order, comment);
	clear();
}

void SalesmanUI::selectDeliveryMethod(Order & order, char & input)
{
	printMenu({"Pickup", "Send"}, "How would you like your pizza delivered?");
	catchCharInput(input, 2, 1);

	if (input == '1') {
		service.setOrderToPickUp(order);
	}
	else if (input == '2') {
		service.setOrderToDelivery(order);
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
				cout << "\t    Size: " << tempPizza.getPizzaSize().getName() << "  \t+" << (tempPizza.getPizzaSize().getPriceMod() - 1) * 100 << " %" << endl;
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
	Takes in input from user and makes sure the input is within a set limit.

	@required-param		char input		"Input that's read"
	@required-param		int max			"Max value that input can recieve"
	@optional-param		int min			"Minimum value that input can recieve",		default-value: 0
	@optional-param		string message	"Message to display when prompting user",	default-value: "Input"
*/
void SalesmanUI::catchCharInput(char& input, const int& max, const int& min, const std::string& msg)
{
	// Keeps prompting the user for input if exception is caught
	while (true)
	{
		try
		{
			getInput(msg, input);
			service.validInput(input, max, min);
			break;
		}
		catch (const InvalidInput& ex)
		{
			printMessage(ex.getMessage());
		}
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
