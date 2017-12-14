#include "SalesmanUI.h"
#include "DeliveryUI.h"
#include "Order.h"
#include "SalesmanService.h"
#include <stdlib.h>

SalesmanUI::SalesmanUI()
{
	_pizzaNumber = 0;
}

void SalesmanUI::salesmanMenu() {
	makeNewOrder();
}

//Let the user pick from menu
void SalesmanUI::makeNewOrder()
{
	Order order;
	SalesmanService service;
	bool pizzaFromMenu = false;
	string input;
	int nrOfOrder = 1;
	
	selectLocation(order, input);
	clear();
	while (true) {
		try
		{
			// Prompt the user to make a new order by either
			// selecting from menu or making his own pizza
			newOrderStart(order, pizzaFromMenu, input);

			if (!pizzaFromMenu) {

				makeYourOwnMenu(order, input);
				break;
			}
		}
		catch (FailedOpenFile) {
			cout << "Failed to open a critical file...";
			break;
		}
	}
	clear();
}

void SalesmanUI::pickFromMenu(Order& order, string& input) {
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
		cout << "TOTAL: " << offers.at(i).getPrice() << " kr.- " << endl;
	}
	cout << endl;
	cout << "Which order would you like?\nInput order number: ";
	cin >> input;
	int inputInInt = convertToInt(input);
	
	order = offers.at(inputInInt).getOrder();
}

void SalesmanUI::makeYourOwnMenu(Order& order, string& input)
{
	Pizza newPizza;
	vector<Pizza> allOrderPizzas = order.getPizzas();
	allOrderPizzas.push_back(newPizza);
	order.setPizzas(allOrderPizzas);
	vector<string> makeYourOwnStringVector = 
		{
			"Select crust", 
			"Select size", 
			"Select toppings",
			"Add sides", 
			"Select delivery method",
			"Add comment",
			"Add another pizza", 
			"See order", 
			"Finish"
		};
	while (true)
	{
		printMenu(
			makeYourOwnStringVector, 
			service.getSingleOfferName(order.getPizzas().at(_pizzaNumber)) + " " +  to_string(service.calculateCost(order.getPizzas().at(_pizzaNumber))) + " kr.-"
		);
		catchStringInput(input, makeYourOwnStringVector.size());
		int selection = convertToInt(input);
		clear();

		switch (selection)
		{
		case 1:
			selectCrust(order, input);
			printMessage("Crust added.");
			break;
		case 2:
			selectSize(order, input);
			printMessage("Size added.");
			break;
		case 3:
			selectToppings(order, input);
			printMessage("Toppings added.");
			break;
		case 4:
			selectSides(order, input);
			printMessage("Side added.");
			break;
		case 5:
			selectDeliveryMethod(order, input);
			printMessage("Delivery method added.");
			break;
		case 6:
			addComment(order);
			printMessage("Comment added");
			break;
		case 7:
			// add another pizza
			break;
		case 8:
			// see order
			break;
		case 9:
			finishOrder(order);
			return;
		default:
			return;
		}
	}
}

void SalesmanUI::selectLocation(Order& order, string& input)
{
	vector<Location> locations = service.getItems<Location>();
	vector<string> stringifyLocations;
	for (size_t i = 0; i < locations.size(); i++) {
		stringifyLocations.push_back(locations.at(i).getAddress());
	}
	printMenu({stringifyLocations}, "Please A Select Location");
	catchStringInput(input, locations.size(), 1);
	order.setLocation(locations.at(convertToInt(input)-1));
}


void SalesmanUI::newOrderStart(Order& order, bool& pizzaFromMenu, string& input)
{
	printMenu({"Select from menu", "Make your own pizza!"}, "Make a new order");

	catchStringInput(input, 2, 1);

	if (tolower(convertToInt(input)) == '1') {
		pickFromMenu(order, input);
		pizzaFromMenu = true;
	}
	clear();
}

void SalesmanUI::selectCrust(Order& order, string& input)
{
	vector<PizzaCrust> crusts = service.getItems<PizzaCrust>();
	printMenu(makeStringVector(crusts), "Select the Pizza Crust");
	catchStringInput(input, crusts.size(), 1);

	vector<Pizza> pizzas = order.getPizzas();
	pizzas.at(_pizzaNumber).setCrust(crusts.at(convertToInt(input)));
	order.setPizzas(pizzas);

	clear();
}

void SalesmanUI::selectSize(Order& order, string& input)
{
	vector<PizzaSize> sizes = service.getItems<PizzaSize>();
	printMenu(makeStringVectorFromPizzaSize(sizes), "Select the Pizza Size");
	catchStringInput(input, sizes.size());

	vector<Pizza> pizzas = order.getPizzas();
	pizzas.at(_pizzaNumber).setPizzaSize(sizes.at(convertToInt(input)));
	order.setPizzas(pizzas);

	clear();
}

void SalesmanUI::selectToppings(Order& order, string& input)
{
	vector<Topping> toppings = service.getItems<Topping>();
	while (true)
	{
		printMenu(makeStringVector(toppings), "Select the Toppings");
		
		// Cannot have more than two of each topping so multiply all toppings by 2
		catchStringInput(input, toppings.size()*2, 0, "Please enter the number of toppings");
		int numberOfToppingsInt = convertToInt(input);

		for (int i = 0; i < numberOfToppingsInt; i++) {
			string inputString = "Select topping nr " + to_string(i+1);
			catchStringInput(input, toppings.size(), 1, inputString);
			vector<Pizza> pizzas = order.getPizzas();
			pizzas.at(_pizzaNumber).addToppings(toppings.at(convertToInt(input)-1));
			order.setPizzas(pizzas);
		}
		break;
	}
	clear();
}

void SalesmanUI::selectSides(Order& order, string& input)
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
	catchStringInput(input, sideOrder.size());

	//Set the selected side order in service
	int index = convertToInt(input)-1;
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

void SalesmanUI::selectDeliveryMethod(Order & order, string& input)
{
	printMenu({"Pickup", "Send"}, "How would you like your pizza delivered?");
	catchStringInput(input, 2, 1);

	if (input == "1") {
		service.setOrderToPickUp(order);
	}
	else if (input == "2") {
		service.setOrderToDelivery(order);
	}
	clear();
}

bool SalesmanUI::addAnotherOrder(string& input)
{
	printMenu({ "Yes", "No" }, "Would you like to add another order to this?");
	catchStringInput(input, 2, 1);
	clear();
	if (input == "1") {
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
				cout << "Pizza nr. " << (i + 1) << ": " << endl;
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
			cout << "\t   " << service.getOldPriceOfOrder(order) << "kr.-" << endl;
			cout << "---------------------------" << endl;
		}
	}
	catch (InvalidOrder) {
		cout << "Order is not valid..." << endl;
	}
}

void SalesmanUI::finishOrder(Order& order)
{
	service.registerNewOrder(order);
}

/*
	Takes in input from user and makes sure the input is within a set limit.

	@required-param		string input	"Input that's read"
	@required-param		int max			"Max value that input can recieve"
	@optional-param		int min			"Minimum value that input can recieve",		default-value: 1
	@optional-param		string message	"Message to display when prompting user",	default-value: "Input"
*/
void SalesmanUI::catchStringInput(string& input, const int& max, const int& min, const std::string& msg)
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

Pizza SalesmanUI::getCurrentPizza(Order& order)
{
	return order.getPizzas().at(_pizzaNumber);
}

int SalesmanUI::convertToInt(string& input)
{
	return std::atoi(input.c_str());
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
