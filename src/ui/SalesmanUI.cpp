#include "SalesmanUI.h"
#include "DeliveryUI.h"
#include "Order.h"
#include "SalesmanService.h"
#include <stdlib.h>

SalesmanUI::SalesmanUI()
{
	_pizzaNumber = 0;
}

void
SalesmanUI::salesmanMenu()
{
	makeNewOrder();
}

//Let the user pick from menu
void
SalesmanUI::makeNewOrder()
{
	Order order;
	SalesmanService service;
	bool pizzaFromMenu = false;
	string input;
	int nrOfOrder = 1;

	clear();
	while (true)
	{
		try
		{
			if (!selectLocation(order, input))
			{
				// Prompt the user to make a new order by either
				// selecting from menu or making his own pizza
				while (true)
				{
					if (newOrderStart(order, pizzaFromMenu, input))
					{
						break;
					}
				}
			}
			else
			{
				break;
			}
		}
		catch (FailedOpenFile)
		{
			printMessage("Failed to open a critical file...");
			break;
		}
	}
}

void
SalesmanUI::pickFromMenu(Order &order, string &input)
{
	clear();
	while (true)
	{
		try
		{
			vector<string> names;
			vector<Offer> offers = service.getItems<Offer>();
			for (size_t i = 0; i < offers.size(); i++)
			{
				names.push_back(offers.at(i).getName());
			}
			names.push_back("Go back");
			printMenu(names, "Pizza Menu");
			//See more about the order
			getInput(input);
			int inputInInt = service.convertStringToInt(input) - 1;
			clear();
			//Go back
			if (inputInInt + 1 == names.size())
			{
				break;
			}
			while (true)
			{
				cout << "Offer: " << offers.at(inputInInt).getName() << endl;
				cout << "-----------------------------------" << endl;

				vector<Pizza> tempPizza = offers.at(inputInInt).getOrder().getPizzas();
				for (size_t i = 0; i < tempPizza.size(); ++i)
				{
					cout << "   Crust: " << tempPizza.at(i).getCrust().getName() << "  \t"
						<< tempPizza.at(i).getCrust().getPrice() << " kr.-" << endl;
					cout << "    Size: " << tempPizza.at(i).getPizzaSize().getName() << " \t+"
						<< (tempPizza.at(i).getPizzaSize().getPriceMod() - 1) * 100 << " %" << endl;
					cout << "Toppings: " << endl;
					vector<Topping> tempToppings = tempPizza.at(i).getToppings();
					for (size_t j = 0; j < tempToppings.size(); ++j)
					{
						cout << "\t  " << tempToppings.at(j).getName() << "    \t" << tempToppings.at(j).getPrice()
							<< " kr.-" << endl;

					}
				}
				cout << "Sides: " << endl;
				vector<SideOrder> tempSides = offers.at(inputInInt).getOrder().getSides();
				for (size_t i = 0; i < tempSides.size(); ++i)
				{
					cout << "\t  " << tempSides.at(i).getName() << "    \t" << tempSides.at(i).getPrice() << " kr.-"
						<< endl;

				}
				cout << "TOTAL: " << service.getPriceOfOrder(offers.at(inputInInt).getOrder()) << " kr.- " << endl;
				printMenu({ "Choose offer", "Go back" }, "More info about offer");
				getInput(input);
				if (input == "1")
				{
					Location temp = order.getLocation();
					order = offers.at(inputInInt).getOrder();
					order.setLocation(temp);
					makeYourOwnMenu(order, input, true);
					break;
				}
				if (input == "2")
				{
					clear();
					break;
				}
				else
				{
					clear();
					printMessage("Invalid input");
				}
			}
		}
		catch (out_of_range)
		{
			printMessage("Invalid input");
		}
		catch (InvalidString)
		{
			clear();
			printMessage("Invalid input");
		}
	}
}

void
SalesmanUI::makeYourOwnMenu(Order &order, string &input, const bool &isFromMenu)
{
	clear();
	if (!isFromMenu)
	{
		Pizza newPizza;
		vector<Pizza> allOrderPizzas = order.getPizzas();
		allOrderPizzas.push_back(newPizza);
		order.setPizzas(allOrderPizzas);
	}
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
		"Mark as paid",
		"Finish",
		"Cancel order"
	};
	while (true)
	{
		printMenu(
			makeYourOwnStringVector,
			service.getSingleOfferName(order.getPizzas().at(_pizzaNumber)) + " "
			+ to_string(service.calculateCost(order.getPizzas().at(_pizzaNumber))) + " kr.-"
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
			addAnotherPizza(order);
			printMessage("You are now making a new pizza");
			break;
		case 8:
			showTotalOrder(order, input);
			break;
		case 9:
			markOrderAsPaid(order);
			printMessage("Order has been marked as paid.");
			break;
		case 10:
			finishOrder(order);
			return;
		case 11:
			clear();
			return;
		default:
			return;
		}
	}
}

bool
SalesmanUI::selectLocation(Order &order, string &input)
{
	while (true)
	{
		try
		{
			vector<Location> locations = service.getItems<Location>();
			vector<string> stringifyLocations;
			for (size_t i = 0; i < locations.size(); i++)
			{
				stringifyLocations.push_back(locations.at(i).getAddress());
			}
			stringifyLocations.push_back("Go back");
			printMenu({ stringifyLocations }, "Please A Select Location");
			catchStringInput(input, locations.size() + 1);
			int inputToInt = convertToInt(input);
			if (inputToInt != locations.size() + 1)
			{
				order.setLocation(locations.at(convertToInt(input) - 1));
				clear();
				return false;
			}
			clear();
			return true;
		}
		catch (EmptyVector)
		{
			printMessage("No locations available");
			return true;
		}
		catch (FailedOpenFile)
		{
			printMessage("Failed to open file");
			return true;
		}
	}
}

bool
SalesmanUI::newOrderStart(Order &order, bool &pizzaFromMenu, string &input)
{
	while (true)
	{
		printMenu({ "Select from menu", "Make your own pizza!", "Go back" }, "Make a new order");
		catchStringInput(input, 3, 1);
		if (input == "1")
		{
			try
			{
				pickFromMenu(order, input);
				pizzaFromMenu = true;
				return false;
			}
			catch (EmptyVector)
			{
				printMessage("No offers available");
			}
			catch (FailedOpenFile)
			{
				printMessage("Failed to open file.");
			}
		}
		else if (input == "2")
		{
			makeYourOwnMenu(order, input);
			pizzaFromMenu = false;
			return false;
		}
		else if (input == "3")
		{
			clear();
			return true;
		}
	}
	clear();
	return false;
}

void
SalesmanUI::selectCrust(Order &order, string &input)
{
	vector<PizzaCrust> crusts = service.getItems<PizzaCrust>();
	printMenu(makeStringVector(crusts), "Select the Pizza Crust");
	catchStringInput(input, crusts.size(), 1);

	vector<Pizza> pizzas = order.getPizzas();
	pizzas.at(_pizzaNumber).setCrust(crusts.at(convertToInt(input) - 1));
	order.setPizzas(pizzas);

	clear();
}

void
SalesmanUI::selectSize(Order &order, string &input)
{
	vector<PizzaSize> sizes = service.getItems<PizzaSize>();
	printMenu(makeStringVectorFromPizzaSize(sizes), "Select the Pizza Size");
	catchStringInput(input, sizes.size());

	vector<Pizza> pizzas = order.getPizzas();
	pizzas.at(_pizzaNumber).setPizzaSize(sizes.at(convertToInt(input) - 1));
	order.setPizzas(pizzas);

	clear();
}

void
SalesmanUI::selectToppings(Order &order, string &input)
{
	vector<Topping> toppings = service.getItems<Topping>();
	while (true)
	{
		printMenu(makeStringVector(toppings), "Select the Toppings");

		// Cannot have more than two of each topping so multiply all toppings by 2
		catchStringInput(input, toppings.size() * 2, 0, "Please enter the number of toppings");
		int numberOfToppingsInt = convertToInt(input);

		for (int i = 0; i < numberOfToppingsInt; i++)
		{
			string inputString = "Select topping nr " + to_string(i + 1);
			catchStringInput(input, toppings.size(), 1, inputString);
			vector<Pizza> pizzas = order.getPizzas();
			pizzas.at(_pizzaNumber).addToppings(toppings.at(convertToInt(input) - 1));
			order.setPizzas(pizzas);
		}
		break;
	}
	clear();
}

void
SalesmanUI::selectSides(Order &order, string &input)
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
	int index = convertToInt(input) - 1;
	service.appendToOrder(order, sideOrder.at(index));

	clear();
}

void
SalesmanUI::addComment(Order &order)
{
	string comment = "None";
	getInput("Insert comment: ", comment);
	service.setComments(order, comment);
	clear();
}

void
SalesmanUI::selectDeliveryMethod(Order &order, string &input)
{
	printMenu({ "Pickup", "Send" }, "How would you like your pizza delivered?");
	catchStringInput(input, 2, 1);

	if (input == "1")
	{
		service.setOrderToPickUp(order);
	}
	else if (input == "2")
	{
		service.setOrderToDelivery(order);

		getInput("Home address", input);
		order.setHomeAddress(input);
	}
	clear();
}

void
SalesmanUI::addAnotherPizza(Order &order)
{
	_pizzaNumber = order.getPizzas().size();
	vector<Pizza> pizzas = order.getPizzas();
	pizzas.push_back(Pizza());
	order.setPizzas(pizzas);
}

void
SalesmanUI::showTotalOrder(Order &order, string &input)
{
	while (true)
	{
		vector<Pizza> pizzas = order.getPizzas();
		vector<string> stringify;
		for (int i = 0; i < pizzas.size(); i++)
		{
			stringify.push_back(service.getSingleOfferName(order.getPizzas().at(i)) + " "
				+ to_string(service.calculateCost(order.getPizzas().at(i))) + " kr.-");
		}
		stringify.push_back("Next");
		stringify.push_back("Back");
		printMenu(stringify, "Pizzas in this order (enter number to enter)");
		string ordercontent = "Order consists of ";
		vector<string> orderoffers = service.getOfferNames(order);
		for (size_t i = 0; i < orderoffers.size(); i++)
		{
			ordercontent += orderoffers.at(i);
			if (i != orderoffers.size() - 1)
			{
				ordercontent += ", ";
			}
		}
		printMessage(ordercontent);
		printMessage("Total: " + to_string(service.getPriceOfOrder(order)) + " kr.-");
		catchStringInput(input, pizzas.size() + 2);

		int inputInt = convertToInt(input);
		if (inputInt != pizzas.size() + 1 && inputInt != pizzas.size() + 2)
		{
			for (int i = 0; i < pizzas.size(); i++)
			{
				if (inputInt == i + 1)
				{
					clear();
					showSinglePizza(order, i, input);
					break;
				}
			}
		}
		else
		{
			if (inputInt == pizzas.size() + 1)
			{
				// Next show sides and misc items
				clear();
				showSides(order, input);
			}
			clear();
			return;
		}
	}
}

void
SalesmanUI::showSinglePizza(Order &order, const int &index, string &input)
{
	while (true)
	{
		Pizza pizzaThatIsBeingEdited = order.getPizzas().at(index);
		printMenu({ "Show toppings", "Show crust", "Show size", "Edit pizza", "Delete pizza", "Back" },
			"Viewing " + service.getSingleOfferName(pizzaThatIsBeingEdited));
		catchStringInput(input, 6);

		int inputInt = convertToInt(input);
		if (inputInt != 6)
		{
			switch (inputInt)
			{
			case 1:
				showToppings(pizzaThatIsBeingEdited, input);
				break;
			case 2:
				showCrust(pizzaThatIsBeingEdited, input);
				break;
			case 3:
				showSize(pizzaThatIsBeingEdited, input);
				break;
			case 4:
				selectPizza(index);
				printMessage("You are now editing pizza nr. " + to_string(index + 1));
				return;
			case 5:
				deletePizza(order, index);
				return;
			}
		}
		else
		{
			clear();
			return;
		}
	}
}

void
SalesmanUI::showToppings(Pizza &pizza, string &input)
{
	printMenu(makeStringVector(pizza.getToppings()), "Showing toppings");
	catchStringInput(input, 0, 0);
	clear();
}

void
SalesmanUI::showCrust(Pizza &pizza, string &input)
{
	printMenu({ pizza.getCrust().getName() });
	catchStringInput(input, 0, 0);
	clear();
}

void
SalesmanUI::showSize(Pizza &pizza, string &input)
{
	printMenu({ pizza.getPizzaSize().getName() });
	catchStringInput(input, 0, 0);
	clear();
}

void
SalesmanUI::selectPizza(const int &index)
{
	_pizzaNumber = index;
	clear();
}

void
SalesmanUI::deletePizza(Order &order, const int &index)
{
	vector<Pizza> pizzas = order.getPizzas();
	if (pizzas.size() == 1)
	{
		clear();
		printMessage("You must at least have one pizza");
		return;
	}
	// Removes the selected pizza at index
	pizzas.erase(pizzas.begin() + index);
	order.setPizzas(pizzas);
	if (_pizzaNumber != 0)
	{
		_pizzaNumber -= 1;
	}
	clear();
}

void
SalesmanUI::showSides(Order &order, string &input)
{
	vector<SideOrder> sides = order.getSides();

	vector<string> stringify = makeStringVector(sides);
	stringify.push_back("Back to menu");
	printMenu(stringify, "Sides in your order");
	catchStringInput(input, sides.size() + 1);

	int inputToInt = convertToInt(input);

	if (inputToInt != sides.size() + 1)
	{
		showSingleSide(order, inputToInt - 1, input);
	}
	clear();
}

void
SalesmanUI::showSingleSide(Order &order, const int &index, string &input)
{
	SideOrder sideOrderThatIsBeingEdited = order.getSides().at(index);

	printMenu({ "Delete side", "Back" }, sideOrderThatIsBeingEdited.getName());
	catchStringInput(input, 2);
	int inputToIndex = convertToInt(input);
	if (inputToIndex != 2)
	{
		deleteSide(order, index);
	}
	clear();
}

void
SalesmanUI::deleteSide(Order &order, const int &index)
{
	vector<SideOrder> sides = order.getSides();
	sides.erase(sides.begin() + index);
	order.setSides(sides);

	clear();
}

void
SalesmanUI::markOrderAsPaid(Order &order)
{
	service.setOrderAsPaid(order);
}

void
SalesmanUI::finishOrder(Order &order)
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
void
SalesmanUI::catchStringInput(string &input, const int &max, const int &min, const std::string &msg)
{
	// Keeps prompting the user for input if exception is caught
	while (true)
	{
		try
		{
			getInput(msg, input);
			// If max is equal to 0 and min is set to 0, then don't bother check if input is valid
			if (max != 0 && min != 0)
			{
				service.validInput(input, max, min);
			}
			break;
		}
		catch (const InvalidInput &ex)
		{
			printMessage(ex.getMessage());
		}
		catch (out_of_range)
		{
			printMessage("No numbers larger than int32!");
		}
		catch (InvalidString)
		{
			printMessage("Input is invalid");
		}
	}
}

int
SalesmanUI::convertToInt(string &input)
{
	return std::atoi(input.c_str());
}

/*
Converting the PizzaSize vector to a string vector by
displaying the name and price modifier in a single string
*/
vector<string>
SalesmanUI::makeStringVectorFromPizzaSize(vector<PizzaSize> pizzaSizeVector)
{
	vector<string> returnVector;

	string tempString;
	string convertionString;
	for (size_t i = 0; i < pizzaSizeVector.size(); i++)
	{
		tempString = pizzaSizeVector.at(i).getName();
		tempString += " | +";
		convertionString = to_string((pizzaSizeVector.at(i).getPriceMod() - 1) * 100);
		// Remove trailing 0's
		convertionString.erase(convertionString.find_last_not_of('0') + 1, string::npos);
		// If the last character is a dot, remove it
		if (convertionString[convertionString.size() - 1] == '.')
		{
			convertionString.erase(convertionString.find_last_not_of('.') + 1, string::npos);
		}
		tempString += convertionString;
		tempString += " %";

		returnVector.push_back(tempString);
	}

	return returnVector;
}
