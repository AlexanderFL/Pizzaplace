#include "ManagerUI.h"

/*
*************************************************
PUBLIC FUNCTIONS
*************************************************
*/

ManagerUI::ManagerUI() {}

void
ManagerUI::showMainMenu()
{
	string input;
	while (true)
	{
		printMenu({ "Toppings", "Locations", "Pizza Sizes", "Pizza Crusts", "Sides", "Offers", "Orders", "Back" },
			"Manager Menu");
		getInput(input);
		clear();
		if (input == "1")
		{
			showToppingsMenu();
		}
		else if (input == "2")
		{
			showLocationsMenu();
		}
		else if (input == "3")
		{
			showSizeMenu();
		}
		else if (input == "4")
		{
			showCrustMenu();
		}
		else if (input == "5")
		{
			showSidesMenu();
		}
		else if (input == "6")
		{
			showOffersMenu();
		}
		else if (input == "7")
		{
			showOrders();
		}
		else if (input == "8")
		{
			return;
		}
		else
		{
			printMessage("Invalid input.");
		}
	}
}

/*
*************************************************
PRIVATE FUNCTIONS
*************************************************
*/

/*
******************************************
TOPPINGS
******************************************
*/

void
ManagerUI::showToppingsMenu()
{
	string input;
	while (true)
	{
		printMenu({ "Create Topping", "Delete Topping", "View Toppings", "Back" }, "Toppings Menu");
		getInput(input);
		clear();
		if (input == "1")
		{
			showToppingCreationMenu();
		}
		else if (input == "2")
		{
			showToppingDeleteMenu();
		}
		else if (input == "3")
		{
			showToppingViewMenu();
		}
		else if (input == "4")
		{
			break;
		}
		else
		{
			clear();
			printMessage("Invalid input.");
		}
	}
}

void
ManagerUI::showToppingCreationMenu()
{
	string input;
	printMessage("Creating a new Topping");
	try
	{
		string name;
		getInput("Name", name);
		//validating name
		service.containsOnlyAlpha(name);
		getInput("Price", input);
		int price = service.convertStringToInt(input);
		//validating price
		service.validPrice(price);
		service.addItem<Topping>(Topping(name, price));
		clear();
		printMessage("Topping was created.");
	}
	catch (NumberInString)
	{
		clear();
		printMessage("Invalid name.");
	}
	catch (InvalidString)
	{
		clear();
		printMessage("Invalid price.");
	}
	catch (InvalidPrice)
	{
		clear();
		printMessage("Invalid price.");
	}
}

void
ManagerUI::showToppingDeleteMenu()
{
	string input;
	while (true)
	{
		try
		{
			vector<Topping> toppings = service.getItems<Topping>();
			vector<string> names;
			for (size_t i = 0; i < toppings.size(); ++i)
			{
				names.push_back(toppings.at(i).getName());
			}
			names.push_back("Back");
			printMenu(names, "Toppings");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size())
			{
				clear();
				break;
			}
			else
			{
				service.deleteItem<Topping>(index - 1);
				clear();
				printMessage("Topping deleted.");
			}
		}
		catch (InvalidString)
		{
			clear();
			printMessage("Invalid input");
		}
		catch (out_of_range)
		{
			clear();
			printMessage("Invalid input.");
		}
		catch (EmptyVector)
		{
			clear();
			printMessage("There are currently no toppings.");
		}
		catch (FailedOpenFile)
		{
			clear();
			printMessage("There are currently no toppings.");
		}
	}
}

void
ManagerUI::showToppingViewMenu()
{
	string input;
	while (true)
	{
		try
		{
			vector<Topping> toppings = service.getItems<Topping>();
			vector<string> names = service.getNames<Topping>();
			names.push_back("Back");
			printMenu(names, "Toppings");
			getInput(input);
			int index = service.convertStringToInt(input);

			if (index < names.size())
			{
				clear();
				editTopping(index - 1);
			}
			else if (index == names.size())
			{
				clear();
				break;
			}
			else
			{
				clear();
				printMessage("Invalid input.");
			}
		}
		catch (InvalidString)
		{
			clear();
			printMessage("Invalid input.");
		}
		catch (EmptyVector)
		{
			clear();
			printMessage("There are currently no toppings.");
			break;
		}
		catch (FailedOpenFile)
		{
			clear();
			printMessage("There are currently no toppings.");
			break;
		}
	}
}

void
ManagerUI::editTopping(int index)
{
	string input;
	try
	{
		Topping toppingToEdit = service.getItem<Topping>(index);
		while (true)
		{
			printMenu({ "Edit name", "Edit price", "Back" }, ("Edit topping %s", toppingToEdit.getName()));
			getInput(input);

			if (input == "1")
			{
				printMessage("Changing name");
				getInput(input);
				try
				{
					service.containsOnlyAlpha(input);
					toppingToEdit.setName(input);
					service.replaceToppingInFile(toppingToEdit, index);
					clear();
					printMessage("Topping was successfully renamed");
				}
				catch (NumberInString)
				{
					printMessage("Number in string name is not valid");
				}
			}
			else if (input == "2")
			{
				printMessage("Changing price");
				getInput(input);
				try
				{
					service.validateStringIsDigit(input);
					int value = atoi(input.c_str());
					toppingToEdit.setPrice(value);
					service.replaceToppingInFile(toppingToEdit, index);
					clear();
					printMessage("Topping was successufully edited");
				}
				catch (InvalidString)
				{
					clear();
					printMessage("Number can't be empty");
				}
				catch (NumberInString)
				{
					clear();
					printMessage("Number can't contain a character");
				}
			}
			else if (input == "3")
			{
				clear();
				break;
			}
			else
			{
				clear();
				printMessage("Invalid index.");
			}
		}
	}
	catch (out_of_range)
	{
		clear();
		printMessage("Invalid index");
	}
}

/*
******************************************
LOCATIONS
******************************************
*/

void
ManagerUI::showLocationsMenu()
{
	string input;
	while (true)
	{
		printMenu({ "Add a loctation", "Delete a location", "See all locations", "Back" }, "Location Menu");
		getInput(input);
		clear();
		if (input == "1")
		{
			showLocationCreationMenu();
		}
		else if (input == "2")
		{
			showLocationDeleteMenu();
		}
		else if (input == "3")
		{
			showLocationViewMenu();
		}
		else if (input == "4")
		{
			return;
		}
		else
		{
			clear();
			printMessage("Not a valid option.");
		}
	}
}

void
ManagerUI::showLocationCreationMenu()
{
	string input;
	printMessage("Creating a new Location");
	try
	{
		string name;
		getInput("Name", name);
		//validating name
		service.containsOnlyAlpha(name);
		service.addItem<Location>(Location(name));
		clear();
		printMessage("Location was created.");
	}
	catch (NumberInString)
	{
		clear();
		printMessage("Invalid name.");
	}
	catch (InvalidString)
	{
		clear();
		printMessage("Invalid name.");
	}
}

void
ManagerUI::showLocationDeleteMenu()
{
	string input;
	while (true)
	{
		try
		{
			vector<Location> locations = service.getItems<Location>();
			vector<string> names = service.getNames<Location>();
			names.push_back("Back");
			printMenu(names, "Deleting a location");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size())
			{
				clear();
				break;
			}
			else
			{
				clear();
				service.deleteItem<Location>(index - 1);
				printMessage("Location deleted.");
				break;
			}
		}
		catch (InvalidString)
		{
			clear();
			printMessage("Invalid input.");
		}
		catch (out_of_range)
		{
			clear();
			printMessage("Invalid input.");
		}
		catch (EmptyVector)
		{
			clear();
			printMessage("There are currently no locations available.");
			break;
		}
		catch (FailedOpenFile)
		{
			clear();
			printMessage("There are currently no locations available.");
			break;
		}
	}
}

void
ManagerUI::showLocationViewMenu()
{
	string input;
	while (true)
	{
		try
		{
			vector<Location> locations = service.getItems<Location>();
			vector<string> names;
			for (size_t i = 0; i < locations.size(); ++i)
			{
				names.push_back(locations.at(i).getAddress());
			}
			names.push_back("Back");
			printMenu(names, "Locations");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size())
			{
				clear();
				break;
			}
			else
			{
				clear();
				printMessage("Not a valid option.");
			}
		}
		catch (InvalidString)
		{
			clear();
			printMessage("Invalid input.");
		}
		catch (EmptyVector)
		{
			clear();
			printMessage("There are currently no locations available.");
			break;
		}
		catch (FailedOpenFile)
		{
			clear();
			printMessage("There are currently no locations available.");
			break;
		}
	}
}
/*
******************************************
SIZES
******************************************
*/
void
ManagerUI::showSizeMenu()
{
	string input;
	while (true)
	{
		printMenu({ "Create a size", "Delete a size", "View sizes", "Back" }, "Pizza size Menu");
		getInput(input);
		clear();
		if (input == "1")
		{
			showSizeCreationMenu();
		}
		else if (input == "2")
		{
			showSizesDeleteMenu();
		}
		else if (input == "3")
		{
			showSizeViewMenu();
		}
		else if (input == "4")
		{
			break;
		}
		else
		{
			clear();
			printMessage("Invalid input.");
		}
	}
}

void
ManagerUI::showSizeCreationMenu()
{
	string input;
	printMessage("Creating a new size");
	try
	{
		string size;
		string name;
		getInput("Name", name);
		//validating name
		service.containsOnlyAlpha(name);
		getInput("Percentage for price increment", size);
		int sizeInInt = service.convertStringToInt(size);
		//validating size
		service.validPrice(sizeInInt);
		service.addItem<PizzaSize>(PizzaSize(name, sizeInInt / 100));
		clear();
		printMessage("Pizza size was created.");
	}
	catch (NumberInString)
	{
		clear();
		printMessage("Invalid name");
	}
	catch (InvalidString)
	{
		clear();
		printMessage("Invalid size.");
	}
	catch (EmptyVector)
	{
		clear();
		printMessage("There are currently no sizes available.");
	}
}

void
ManagerUI::showSizesDeleteMenu()
{
	string input;
	while (true)
	{
		try
		{
			vector<PizzaSize> sizes = service.getItems<PizzaSize>();
			vector<string> names;
			for (size_t i = 0; i < sizes.size(); ++i)
			{
				names.push_back(sizes.at(i).getName() + " " + to_string(sizes.at(i).getPriceMod()));
			}
			names.push_back("Back");
			printMenu(names, "Deleting a size");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size())
			{
				clear();
				break;
			}
			else
			{
				clear();
				service.deleteItem<PizzaSize>(index - 1);
				printMessage("Size deleted.");
				break;
			}
		}
		catch (InvalidString)
		{
			clear();
			printMessage("Invalid input");
		}
		catch (out_of_range)
		{
			clear();
			printMessage("Invalid input.");
		}
		catch (EmptyVector)
		{
			clear();
			printMessage("There are currently no sizes available.");
			break;
		}
		catch (FailedOpenFile)
		{
			clear();
			printMessage("There are currently no sizes available.");
			break;
		}
	}
}

void
ManagerUI::showSizeViewMenu()
{
	string input;
	while (true)
	{
		try
		{
			vector<PizzaSize> sizes = service.getItems<PizzaSize>();
			vector<string> names;
			for (size_t i = 0; i < sizes.size(); ++i)
			{
				names.push_back(sizes.at(i).getName() + " " + to_string(sizes.at(i).getPriceMod()));
			}
			names.push_back("Back");
			printMenu(names, "Pizza sizes");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size())
			{
				clear();
				break;
			}
			else
			{
				clear();
				printMessage("Invalid input.");
			}
		}
		catch (InvalidString)
		{
			clear();
			printMessage("Invalid input");
		}
		catch (EmptyVector)
		{
			clear();
			printMessage("There are currently no sizes available.");
			break;
		}
		catch (FailedOpenFile)
		{
			clear();
			printMessage("There are currently no sizes available.");
			break;
		}
	}
}

/*
******************************************
CRUST
******************************************
*/

void
ManagerUI::showCrustMenu()
{
	string input;
	while (true)
	{
		printMenu({ "Create a crust", "Delete a crust", "View crusts", "Back" }, "Pizza crust Menu");
		getInput(input);
		clear();
		if (input == "1")
		{
			showCrustCreationMenu();
		}
		else if (input == "2")
		{
			showCrustDeleteMenu();
		}
		else if (input == "3")
		{
			showCrustViewMenu();
		}
		else if (input == "4")
		{
			break;
		}
		else
		{
			clear();
			printMessage("Invalid input.");
		}
	}
}

void
ManagerUI::showCrustCreationMenu()
{
	string input;
	printMessage("Creating a new crust");
	try
	{
		string price;
		string name;
		getInput("Name", name);
		//validating name
		service.containsOnlyAlpha(name);
		getInput("Price", price);
		int priceInInt = service.convertStringToInt(price);
		//validating price
		service.validPrice(priceInInt);
		service.addItem<PizzaCrust>(PizzaCrust(name, priceInInt));
		clear();
		printMessage("Pizza crust was created.");
	}
	catch (NumberInString)
	{
		clear();
		printMessage("Invalid name");
	}
	catch (InvalidString)
	{
		clear();
		printMessage("Invalid price.");
	}
}

void
ManagerUI::showCrustDeleteMenu()
{
	string input;
	while (true)
	{
		try
		{
			vector<PizzaCrust> crusts = service.getItems<PizzaCrust>();
			vector<string> names;
			for (size_t i = 0; i < crusts.size(); ++i)
			{
				names.push_back(crusts.at(i).getName() + " " + to_string(crusts.at(i).getPrice()));
			}
			names.push_back("Back");
			printMenu(names, "Deleting pizza crust");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size())
			{
				clear();
				break;
			}
			else
			{
				clear();
				service.deleteItem<PizzaCrust>(index - 1);
				printMessage("Crust deleted.");
				break;
			}
		}
		catch (InvalidString)
		{
			clear();
			printMessage("Invalid input");
		}
		catch (out_of_range)
		{
			clear();
			printMessage("Invalid input.");
		}
		catch (EmptyVector)
		{
			clear();
			printMessage("There are currently no crusts available.");
			break;
		}
		catch (FailedOpenFile)
		{
			clear();
			printMessage("There are currently no crusts available.");
			break;
		}
	}
}

void
ManagerUI::showCrustViewMenu()
{
	string input;
	while (true)
	{
		try
		{
			vector<PizzaCrust> crusts = service.getItems<PizzaCrust>();
			vector<string> names;
			for (size_t i = 0; i < crusts.size(); ++i)
			{
				names.push_back(crusts.at(i).getName() + " " + to_string(crusts.at(i).getPrice()));
			}
			names.push_back("Back");
			printMenu(names, "Pizza crusts");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size())
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
		catch (InvalidString)
		{
			clear();
			printMessage("Invalid input");
		}
		catch (EmptyVector)
		{
			clear();
			printMessage("There are currently no crusts available.");
			break;
		}
		catch (FailedOpenFile)
		{
			clear();
			printMessage("There are currently no crusts available.");
			break;
		}
	}
}

/*
******************************************
SIDES
******************************************
*/
void
ManagerUI::showSidesMenu()
{
	string input;
	clear();
	while (true)
	{
		printMenu({ "Create a side", "Delete a side", "View sides", "Back" }, "Sides Menu");
		getInput(input);
		clear();
		if (input == "1")
		{
			showSidesCreationMenu();
		}
		else if (input == "2")
		{
			showSidesDeleteMenu();
		}
		else if (input == "3")
		{
			showSidesViewMenu();
		}
		else if (input == "4")
		{
			clear();
			break;
		}
		else
		{
			clear();
			printMessage("Invalid input.");
		}
	}
}

void
ManagerUI::showSidesCreationMenu()
{
	string input;
	printMessage("Creating a new side");
	try
	{
		string price;
		string name;
		getInput("Name", name);
		service.containsOnlyAlpha(name);
		getInput("Price", price);
		int priceInInt = service.convertStringToInt(price);
		service.validPrice(priceInInt);
		service.addItem<SideOrder>(SideOrder(name, priceInInt));
		clear();
		printMessage("Pizza side was created.");
	}
	catch (NumberInString)
	{
		clear();
		printMessage("Invalid name");
	}
	catch (InvalidString)
	{
		clear();
		printMessage("Invalid price.");
	}
}

void
ManagerUI::showSidesDeleteMenu()
{
	string input;
	while (true)
	{
		try
		{
			vector<SideOrder> sides = service.getItems<SideOrder>();
			vector<string> names;
			for (size_t i = 0; i < sides.size(); ++i)
			{
				names.push_back(sides.at(i).getName() + " " + to_string(sides.at(i).getPrice()));
			}
			names.push_back("Back");
			printMenu(names, "Sides");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size())
			{
				clear();
				break;
			}
			else
			{
				clear();
				service.deleteItem<SideOrder>(index - 1);
				printMessage("Side deleted.");
				break;
			}
		}
		catch (InvalidString)
		{
			clear();
			printMessage("Invalid input.");
		}
		catch (out_of_range)
		{
			clear();
			printMessage("Invalid input.");
		}
		catch (EmptyVector)
		{
			clear();
			printMessage("There are currently no sides available.");
			break;
		}
		catch (FailedOpenFile)
		{
			clear();
			printMessage("There are currently no sides available.");
			break;
		}
	}
}

void
ManagerUI::showSidesViewMenu()
{
	string input;
	while (true)
	{
		try
		{
			vector<SideOrder> sides = service.getItems<SideOrder>();
			vector<string> names;
			for (size_t i = 0; i < sides.size(); ++i)
			{
				names.push_back(sides.at(i).getName() + " " + to_string(sides.at(i).getPrice()));
			}
			names.push_back("Back");
			printMenu(names, "Sides");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size())
			{
				clear();
				break;
			}
			else
			{
				clear();
				printMessage("Invalid input.");
			}
		}
		catch (InvalidString)
		{
			clear();
			printMessage("Invalid input.");
		}
		catch (EmptyVector)
		{
			clear();
			printMessage("There are currently no sides available.");
			break;
		}
		catch (FailedOpenFile)
		{
			clear();
			printMessage("There are currently no sides available.");
			break;
		}
	}
}

/*
******************************************
OFFERS
******************************************
*/


void
ManagerUI::showOffersMenu()
{
	string input;
	while (true)
	{
		printMenu({ "Create Offer", "View Offers", "Delete Offer", "Back" }, "Offers Menu");
		getInput(input);

		if (input == "1")
		{
			clear();
			showOfferCreationMenu();
		}
		else if (input == "2")
		{
			clear();
			showOfferViewMenu();
		}
		else if (input == "3")
		{
			clear();
			showOfferDeleteMenu();
		}
		else if (input == "4")
		{
			clear();
			return;
		}
		else
		{
			clear();
			printMessage("Invalid input.");
		}
	}
}

void
ManagerUI::showOfferCreationMenu()
{
	string input;
	Offer offer;
	vector<Pizza> pizzas;
	vector<SideOrder> sides;
	while (true)
	{
		printMenu({ "Set Name", "Set Price", "Create Pizza", "Delete Pizza", "Add Side", "Delete Side", "Complete",
			"Cancel"
		}, "Offer - " + offer.getName());
		getInput(input);
		if (input == "1")
		{
			getInput("Name", input);
			offer.setName(input);
			clear();
		}
		else if (input == "2")
		{
			getInput("Procent Discount (1-100)", input);
			try
			{
				int price = service.convertStringToInt(input);
				service.validProcent(price);
				// 100 - x because 100% - 25% = 75% price
				offer.setPrice(100 - price);
				clear();
			}
			catch (InvalidString)
			{
				clear();
				printMessage("Invalid Price. (1-100)");
			}
			catch (InvalidPrice)
			{
				clear();
				printMessage("Invalid Price. (1-100)");
			}
		}
		else if (input == "3")
		{
			clear();
			try
			{
				Pizza pizza;
				showCreatePizzaMenu(pizza);
				pizzas.push_back(pizza);
			}
			catch (Canceled)
			{
				clear();
				printMessage("Pizza Canceled.");
			}
		}
		else if (input == "4")
		{
			clear();
			while (true)
			{
				try
				{
					vector<string> names;
					for (size_t i = 0; i < pizzas.size(); ++i)
					{
						names.push_back("Pizza with " + to_string(pizzas.at(i).getToppings().size()) + " toppings");
					}
					service.validateVectorNotEmpty(names);
					names.push_back("Back");
					printMenu(names, "Current Pizzas");
					getInput(input);
					int index = service.convertStringToInt(input);
					if (index == names.size())
					{
						clear();
						break;
					}
					else
					{
						pizzas = service.deleteItem(pizzas, index - 1);
						clear();
						printMessage("Pizza removed.");
						break;
					}
				}
				catch (InvalidString)
				{
					clear();
					printMessage("Not a valid option.");
				}
				catch (out_of_range)
				{
					clear();
					printMessage("Not a valid option.");
				}
				catch (EmptyVector)
				{
					clear();
					printMessage("No pizzas available.");
					break;
				}
			}
		}
		else if (input == "5")
		{
			clear();
			while (true)
			{
				try
				{
					vector<string> names = service.getNames<SideOrder>();
					names.push_back("Back");
					printMenu(names, "Sides");
					getInput(input);
					int index = service.convertStringToInt(input);
					if (index == names.size())
					{
						clear();
						break;
					}
					else
					{
						sides.push_back(service.getItem<SideOrder>(index - 1));
						clear();
						printMessage("Side added.");
						break;
					}
				}
				catch (InvalidString)
				{
					clear();
					printMessage("Not a valid option.");
				}
				catch (out_of_range)
				{
					clear();
					printMessage("Not a valid option.");
				}
				catch (EmptyVector)
				{
					clear();
					printMessage("No sides available.");
					break;
				}
				catch (FailedOpenFile)
				{
					clear();
					printMessage("No sides available.");
					break;
				}
			}
		}
		else if (input == "6")
		{
			clear();
			while (true)
			{
				try
				{
					vector<string> names = service.getNames(sides);
					service.validateVectorNotEmpty(names);
					names.push_back("Back");
					printMenu(names, "Current Sides");
					getInput(input);
					int index = service.convertStringToInt(input);
					if (index == names.size())
					{
						clear();
						break;
					}
					else
					{
						sides = service.deleteItem(sides, index - 1);
						clear();
						printMessage("Side removed.");
						break;
					}
				}
				catch (InvalidString)
				{
					clear();
					printMessage("Not a valid option.");
				}
				catch (out_of_range)
				{
					clear();
					printMessage("Not a valid option.");
				}
				catch (EmptyVector)
				{
					clear();
					printMessage("No sides available.");
					break;
				}
			}
		}
		else if (input == "7")
		{
			try
			{
				Order order;
				order.setPizzas(pizzas);
				order.setSides(sides);
				offer.setOrder(order);
				service.validateOffer(offer);
				service.addItem<Offer>(offer);
				clear();
				printMessage("Offer completed.");
				return;
			}
			catch (InvalidOffer e)
			{
				clear();
				printMessage(e.getMessage());
			}
		}
		else if (input == "8")
		{
			clear();
			printMessage("Offer canceled.");
			return;
		}

		else
		{
			clear();
			printMessage("Not a valid option.");
		}
	}
}

void
ManagerUI::showOfferViewMenu()
{
	string input;
	while (true)
	{
		try
		{
			vector<Offer> offers = service.getItems<Offer>();
			vector<string> names = service.getNames<Offer>();
			names.push_back("Back");
			printMenu(names, "Offers");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size())
			{
				clear();
				return;
			}
			else
			{
				clear();
				printMessage("Not a valid option.");
			}
		}
		catch (InvalidString)
		{
			clear();
			printMessage("Not a valid option.");
		}
		catch (out_of_range)
		{
			clear();
			printMessage("Not a valid option.");
		}
		catch (EmptyVector)
		{
			clear();
			printMessage("There are currently no offers.");
			break;
		}
		catch (FailedOpenFile)
		{
			clear();
			printMessage("There are currently no offers.");
			break;
		}
	}
}

void
ManagerUI::showOfferDeleteMenu()
{
	string input;
	while (true)
	{
		try
		{
			vector<string> names = service.getNames<Offer>();
			names.push_back("Back");
			printMenu(names, "Offers");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size())
			{
				clear();
				return;
			}
			else
			{
				service.deleteItem<Offer>(index - 1);
				clear();
				printMessage("Offer deleted.");
			}
		}
		catch (InvalidString)
		{
			clear();
			printMessage("Not a valid option.");
		}
		catch (out_of_range)
		{
			clear();
			printMessage("Not a valid option.");
		}
		catch (EmptyVector)
		{
			clear();
			printMessage("There are currently no offers.");
			break;
		}
		catch (FailedOpenFile)
		{
			clear();
			printMessage("There are currently no offers.");
			break;
		}
	}
}

void
ManagerUI::showCreatePizzaMenu(Pizza &pizza)
{
	string input;
	while (true)
	{
		printMenu({ "Add Topping", "Remove Topping", "Complete", "Cancel" }, "Pizza Creator");
		getInput(input);
		if (input == "1")
		{
			clear();
			while (true)
			{
				try
				{
					vector<string> names = service.getNames<Topping>();
					names.push_back("Back");
					printMenu(names, "Toppings");
					getInput(input);
					int index = service.convertStringToInt(input);
					if (index == names.size())
					{
						clear();
						break;
					}
					else
					{
						pizza.addToppings(service.getItem<Topping>(index - 1));
						clear();
						printMessage("Topping added.");
						break;
					}
				}
				catch (InvalidString)
				{
					clear();
					printMessage("Not a valid option.");
				}
				catch (out_of_range)
				{
					clear();
					printMessage("Not a valid option.");
				}
				catch (EmptyVector)
				{
					clear();
					printMessage("No toppings available.");
					break;
				}
				catch (FailedOpenFile)
				{
					clear();
					printMessage("No toppings available.");
					break;
				}
			}
		}
		else if (input == "2")
		{
			clear();
			while (true)
			{
				try
				{
					vector<string> names = service.getNames(pizza.getToppings());
					service.validateVectorNotEmpty(names);
					names.push_back("Back");
					printMenu(names, "Toppings");
					getInput(input);
					int index = service.convertStringToInt(input);
					if (index == names.size())
					{
						clear();
						break;
					}
					else
					{
						pizza.setToppings(service.deleteItem(pizza.getToppings(), index - 1));
						clear();
						printMessage("Topping removed.");
						break;
					}
				}
				catch (InvalidString)
				{
					clear();
					printMessage("Not a valid option.");
				}
				catch (out_of_range)
				{
					clear();
					printMessage("Not a valid option.");
				}
				catch (EmptyVector)
				{
					clear();
					printMessage("No toppings available.");
					break;
				}
			}
		}
		else if (input == "3")
		{
			clear();
			printMessage("Pizza created.");
			return;
		}
		else if (input == "4")
		{
			throw Canceled();
		}
		else
		{
			clear();
			printMessage("Not a valid option.");
		}
	}
}

void
ManagerUI::showOrders()
{
	string input;

	while (true)
	{
		try
		{
			vector<Order> orders = service.getItems<Order>();
			vector<string> names;
			int orderCounter = orders.size();
			for (size_t i = 0; i < orders.size(); ++i)
			{
				names.push_back("Order " + to_string(orders.at(i).getID()));
			}
			names.push_back("Go back");
			printMenu(names, "All orders");
			string message = "Total orders: " + to_string(orderCounter);
			printMessage(message);
			//See more about an order
			getInput(input);
			int order = service.convertStringToInt(input) - 1;
			if (order + 1 == names.size())
			{
				clear();
				break;
			}
			clear();
			while (true)
			{
				showOrderInfo(orders.at(order));
				cout << endl;
				printMenu({ "Delete", "Go Back" }, "More info about order");
				getInput(input);

				if (input == "1")
				{
					clear();
					service.deleteItem<Order>(order);
					printMessage("Order deleted");
					break;
				}
				else if (input == "2")
				{
					clear();
					break;
				}
				else
				{
					clear();
					printMessage("Invalid input.");
				}
			}
		}
		catch (out_of_range)
		{
			clear();
			printMessage("Invalid input.");
		}
		catch (InvalidString)
		{
			clear();
			printMessage("Invalid input");
		}
		catch (EmptyVector)
		{
			clear();
			printMessage("There are currently no orders.");
			break;
		}
		catch (FailedOpenFile)
		{
			clear();
			printMessage("Failed to open file.");
			break;
		}
	}
}
