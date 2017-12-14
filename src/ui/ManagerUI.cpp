#include "ManagerUI.h"

ManagerUI::ManagerUI() {}

void ManagerUI::showMainMenu() {
	string input;
	while (true) {
		printMenu({ "Toppings", "Locations", "Pizza Sizes", "Pizza Crusts", "Sides", "Offers", "Back" }, "Manager Menu");
		getInput(input);
		clear();
		if (input == "1") {
			showToppingsMenu();
		}
		else if (input == "2") {
			showLocationsMenu();
		}
		else if (input == "3") {
			showSizeMenu();
		}
		else if (input == "4") {
			showCrustMenu();
		}
		else if (input == "5") {
			showSidesMenu();

		}
		else if (input == "6") {
			showOffersMenu();
		}
		else if (input == "7") {
			return;
		}
		else {
			clear();
			printMessage("Not a valid option.");
		}
	}
}

/*
******************************************
				TOPPINGS
******************************************
*/

void ManagerUI::showToppingsMenu() {
	string input;
	while (true) {
		printMenu({ "Create Topping", "Delete Topping", "view Toppings", "Back" }, "Toppings Menu");
		getInput(input);
		clear();
		if (input == "1") {
			showToppingCreationMenu();
		}
		else if (input == "2") {
			showToppingDeleteMenu();
		}
		else if (input == "3") {
			showToppingViewMenu();
		}
		else if (input == "4") {
			break;
		}
		else {
			printMessage("Not a valid option.");
		}
	}
}

void ManagerUI::showToppingCreationMenu() {
	string input;
	printMessage("Creating a new Topping");
	try {
		string name;
		getInput("Name", name);
		getInput("Price", input);
		int price = service.convertStringToInt(input);
		service.addItem<Topping>(Topping(name, price));
		clear();
		printMessage("Topping was created.");
	}
	catch (InvalidString) {
		clear();
		printMessage("Invalid name.");
	}
	catch (NumberInString) {
		clear();
		printMessage("Invalid price.");
	}
	catch (InvalidPrice) {
		clear();
		printMessage("Invalid price.");
	}
}

void ManagerUI::showToppingDeleteMenu() {
	string input;
	try {
		while (true) {
			vector<Topping> toppings = service.getItems<Topping>();
			vector<string> names;
			for (size_t i = 0; i < toppings.size(); ++i) {
				names.push_back(toppings.at(i).getName());
			}
			names.push_back("Back");
			printMenu(names, "Toppings");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size()) {
				clear();
				break;
			}
			else {
				try {
					service.deleteItem<Topping>(index - 1);
					clear();
					printMessage("Topping deleted.");
				}
				catch (out_of_range) {
					clear();
					printMessage("Not a valid option.");
				}
			}
		}
	}
	catch (EmptyVector) {
		clear();
		printMessage("There are currently no toppings.");
	}
}

void ManagerUI::showToppingViewMenu() {
	string input;
	try {
		while (true) {
			vector<Topping> toppings = service.getItems<Topping>();
			vector<string> names = service.getNames<Topping>();
			names.push_back("Back");
			printMenu(names, "Toppings");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index < names.size()) {
				clear();
				editTopping(toppings, index-1);
			}
			else if (index == names.size()) {
				clear();
				break;
			}
			else {
				clear();
				printMessage("Not a valid option.");
			}
		}
	} 
	catch (EmptyVector) {
		clear();
		printMessage("There are currently no toppings.");
	}
}

void ManagerUI::editTopping(vector<Topping> toppings, int index)
{
	string input;
	Topping toppingToEdit = toppings[index];
	while (true)
	{
		printMenu({ "Edit name", "Edit price", "Back" }, ("Edit topping %s", toppingToEdit.getName()));
		getInput(input);

		if (input == "1") {
			printMessage("Changing name");
			getInput(input);
			try {
				service.containsOnlyAlpha(input);
				toppingToEdit.setName(input);
				service.replaceToppingInFile(toppingToEdit, index);
				clear();
				printMessage("Topping was successfully renamed");
			}
			catch (NumberInString) {
				printMessage("Number in string name is not valid");
			}
		}
		else if (input == "2") {
			printMessage("Changing price");
			getInput(input);
			try {
				service.validateStringIsDigit(input);
				int value = atoi(input.c_str());
				toppingToEdit.setPrice(value);
				service.replaceToppingInFile(toppingToEdit, index);
				clear();
				printMessage("Topping was successufully edited");
			}
			catch (InvalidString) {
				clear();
				printMessage("Number can't be empty");
			}
			catch (NumberInString) {
				clear();
				printMessage("Number can't contain a character");
			}
		}
		else if (input == "3") {
			clear();
			break;
		}
		else {
			system("CLS");
			printMessage("Invalid index.");
		}
	}
}


/*
******************************************
				LOCATIONS
******************************************
*/

void ManagerUI::showLocationsMenu() {
	string input;
	while (true) {
		printMenu({ "Add a loctation", "Delete a location", "see all locations", "Back" }, "Location Menu");
		getInput(input);
		clear();
		if (input == "1") {
			showLocationCreationMenu();
		}
		else if (input == "2") {
			showLocationDeleteMenu();
		}
		else if (input == "3") {
			showLocationViewMenu();
		}
		else if (input == "4") {
			return;
		}
		else {
			clear();
			printMessage("Not a valid option.");
		}
	}
}

void ManagerUI::showLocationCreationMenu() {
	string input;
	printMessage("Creating a new Location");
	try {
		string name;
		getInput("Name", name);
		service.addItem<Location>(Location(name));
		clear();
		printMessage("Location was created.");
	}
	catch (InvalidString) {
		clear();
		printMessage("Invalid name.");
	}
}

void ManagerUI::showLocationDeleteMenu() {
	string input;
	try {
		while (true) {
			vector<Location> locations = service.getItems<Location>();
			vector<string> names;
			for (size_t i = 0; i < locations.size(); ++i) {
				names.push_back(locations.at(i).getAddress());
			}
			names.push_back("Back");
			printMenu(names, "Deleting a location");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size()) {
				break;
			}
		else {
				try {
					clear();
					service.deleteItem<Location>(index - 1);
					printMessage("Location deleted.");
				}
				catch (out_of_range) {
					clear();
				printMessage("Not a valid option.");
				}
			}
		}
	}
	catch (EmptyVector) {
		printMessage("There are currently no locations available.");
	}
}

void ManagerUI::showLocationViewMenu() {
	string input;
	try {
		while (true) {
			vector<Location> locations = service.getItems<Location>();
			vector<string> names;
			for (size_t i = 0; i < locations.size(); ++i) {
				names.push_back(locations.at(i).getAddress());
			}
			names.push_back("Back");
			printMenu(names, "Locations");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size()) {
				break;
			}
			else {
				printMessage("Not a valid option.");
			}
		}
	}
	catch (EmptyVector) {
		printMessage("There are currently no locations available.");
	}
}
/*
******************************************
				SIZES
******************************************
*/
void ManagerUI::showSizeMenu() {
	string input;
	while (true) {
		clear();
		printMenu({ "Create a size", "Delete a size", "View sizes", "Back" }, "Pizza size Menu");
		getInput(input);
		clear();
		if (input == "1") {
			showSizeCreationMenu();
		}
		else if (input == "2") {
			showSizesDeleteMenu();
		}
		else if (input == "3") {
			showSizeViewMenu();
		}
		else if (input == "4") {
			break;
		}
		else {
			printMessage("Not a valid option.");
		}
	}
}

void ManagerUI::showSizeCreationMenu() {
	string input;
	printMessage("Creating a new size");
	try {
		string size;
		string name;
		getInput("Name", name);
		getInput("Size", size);
		int sizeInInt  = service.convertStringToInt(size);
		//Verify to check if it is not valid
		service.addItem<PizzaSize>(PizzaSize(name, sizeInInt));
		clear();
		printMessage("Pizza size was created.");
	}
	catch (InvalidString) {
		clear();
		printMessage("Invalid input.");
	}
}

void ManagerUI::showSizesDeleteMenu() {
	string input;
	try {
		while (true) {
			vector<PizzaSize> sizes = service.getItems<PizzaSize>();
			vector<string> names;
			for (size_t i = 0; i < sizes.size(); ++i) {
				names.push_back(sizes.at(i).getName() + " " + to_string(sizes.at(i).getPriceMod()));
			}
			names.push_back("Back");
			printMenu(names, "Deleting a size");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size()) {
				break;
			}
			else {
				try {
					clear();
					service.deleteItem<PizzaSize>(index - 1);
					printMessage("Size deleted.");
				}
				catch (out_of_range) {
					clear();
					printMessage("Not a valid option.");
				}
			}
		}
	}
	catch (EmptyVector) {
		printMessage("There are currently no sizes available.");
	}
}

void ManagerUI::showSizeViewMenu() {
	string input;
	try {
		while (true) {
			vector<PizzaSize> sizes = service.getItems<PizzaSize>();
			vector<string> names;
			for (size_t i = 0; i < sizes.size(); ++i) {
				names.push_back(sizes.at(i).getName() + " " + to_string(sizes.at(i).getPriceMod()));
			}
			names.push_back("Back");
			printMenu(names, "Pizza sizes");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size()) {
				break;
			}
			else {
				printMessage("Not a valid option.");
			}
		}
	}
	catch (EmptyVector) {
		printMessage("There are currently no sizes available.");
	}
}


/*
******************************************
				CRUST
******************************************
*/

void ManagerUI::showCrustMenu() {
	string input;
	while (true) {
		clear();
		printMenu({ "Create a crust", "Delete a crust", "View crusts", "Back" }, "Pizza crust Menu");
		getInput(input);
		clear();
		if (input == "1") {
			showCrustCreationMenu();
		}
		else if (input == "2") {
			showCrustDeleteMenu();
		}
		else if (input == "3") {
			showCrustViewMenu();
		}
		else if (input == "4") {
			break;
		}
		else {
			printMessage("Not a valid option.");
		}
	}
}

void ManagerUI::showCrustCreationMenu() {
	string input;
	printMessage("Creating a new crust");
	try {
		string price;
		string name;
		getInput("Name", name);
		getInput("Price", price);
		int priceInInt = service.convertStringToInt(price);
		//Verify to check if it is not valid
		service.addItem<PizzaCrust>(PizzaCrust(name, priceInInt));
		clear();
		printMessage("Pizza crust was created.");
	}
	catch (InvalidString) {
		clear();
		printMessage("Invalid input.");
	}
}

void ManagerUI::showCrustDeleteMenu() {
	string input;
	try {
		while(true){
		vector<PizzaCrust> crusts = service.getItems<PizzaCrust>();
		vector<string> names;
		for (size_t i = 0; i < crusts.size(); ++i) {
			names.push_back(crusts.at(i).getName() + " " + to_string(crusts.at(i).getPrice()));
		}
		names.push_back("Back");
		printMenu(names, "Deleting pizza crust");
		getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size()) {
				break;
			}
			else {
				try {
					clear();
					service.deleteItem<PizzaCrust>(index - 1);
					printMessage("Crust deleted.");
				}
				catch (out_of_range) {
					clear();
					printMessage("Not a valid option.");
				}
			}
		}
	}
	catch (EmptyVector) {
		printMessage("There are currently no crusts available.");
	}
}

void ManagerUI::showCrustViewMenu() {
	string input;
	try {
		while (true) {
			vector<PizzaCrust> crusts = service.getItems<PizzaCrust>();
			vector<string> names;
			for (size_t i = 0; i < crusts.size(); ++i) {
				names.push_back(crusts.at(i).getName() + " " + to_string(crusts.at(i).getPrice()));
			}
			names.push_back("Back");
			printMenu(names, "Pizza crusts");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size()) {
				break;
			}
			else {
				printMessage("Not a valid option.");
			}
		}
	}
	catch (EmptyVector) {
		printMessage("There are currently no crusts available.");
	}
}

/*
******************************************
				SIDES
******************************************
*/
void ManagerUI::showSidesMenu() {
	string input;
	clear();
	while (true) {
		printMenu({ "Create a side", "Delete a side", "View sides", "Back" }, "Sides Menu");
		getInput(input);
		clear();
		if (input == "1") {
			showSidesCreationMenu();
		}
		else if (input == "2") {
			showSidesDeleteMenu();
		}
		else if (input == "3") {
			showSidesViewMenu();
		}
		else if (input == "4") {
			break;
		}
		else {
			printMessage("Not a valid option.");
		}
	}
}

void ManagerUI::showSidesCreationMenu() {
	string input;
	printMessage("Creating a new side");
	try {
		string price;
		string name;
		getInput("Name", name);
		getInput("Price", price);
		int priceInInt = service.convertStringToInt(price);
		//Verify to check if it is not valid
		service.addItem<SideOrder>(SideOrder(name, priceInInt));
		clear();
		printMessage("Pizza side was created.");
	}
	catch (InvalidString) {
		clear();
		printMessage("Invalid input.");
	}
}


void ManagerUI::showSidesDeleteMenu() {
	string input;
	try {
		while (true) {
			vector<SideOrder> sides = service.getItems<SideOrder>();
			vector<string> names;
			for (size_t i = 0; i < sides.size(); ++i) {
				names.push_back(sides.at(i).getName() + " " + to_string(sides.at(i).getPrice()));
			}
			names.push_back("Back");
			printMenu(names, "Sides");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size()) {
				break;
			}
			else {
				try {
					clear();
					service.deleteItem<SideOrder>(index - 1);
					printMessage("Side deleted.");
				}
				catch (out_of_range) {
					clear();
					printMessage("Not a valid option.");
				}
			}
		}
	}
	catch (EmptyVector) {
		printMessage("There are currently no sides available.");
	}
}

void ManagerUI::showSidesViewMenu() {
	string input;
	try {
		while (true) {
			vector<SideOrder> sides = service.getItems<SideOrder>();
			vector<string> names;
			for (size_t i = 0; i < sides.size(); ++i) {
				names.push_back(sides.at(i).getName() + " " + to_string(sides.at(i).getPrice()));
			}
			names.push_back("Back");
			printMenu(names, "Sides");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size()) {
				break;
			}
			else {
				printMessage("Not a valid option.");
			}
		}
	}
	catch (EmptyVector) {
		printMessage("There are currently no sides available.");
	}
}

/*
******************************************
				OFFERS
******************************************
*/


void ManagerUI::showOffersMenu() {
	string input;
	while (true) {
		printMenu({ "Create Offer", "View Offers", "Delete Offer", "Back" }, "Offers Menu");
		getInput(input);
		
		if (input == "1") {
			clear();
			showOfferCreationMenu();
		}
		else if (input == "2") {
			clear();
			showOfferViewMenu();
		}
		else if (input == "3") {
			clear();
			showOfferDeleteMenu();
		}
		else if (input == "4") {
			clear();
			return;
		}
		else {
			clear();
			printMessage("Not a valid option.");
		}
	}
}

void ManagerUI::showOfferCreationMenu() {
	string input;
	Offer offer;
	vector<Pizza> pizzas;
	vector<SideOrder> sides;
	while (true) {
		printMenu({ "Set Name", "Set Price", "Create Pizza", "Delete Pizza", "Add Side", "Delete Side", "Complete", "Cancel" }, "Offer - " + offer.getName());
		getInput(input);
		if (input == "1") {
			getInput("Name", input);
			//Validate name
			offer.setName(input);
			clear();
		}
		else if (input == "2") {
			getInput("Price", input);
			try {
				int price = service.convertStringToInt(input);
				//Validate price
				offer.setPrice(price);
				clear();
			}
			catch (NumberInString) {
				clear();
				printMessage("Invalid Price.");
			}
		}
		else if (input == "3") {
			clear();
			Pizza pizza;
			showCreatePizzaMenu(pizza);
			pizzas.push_back(pizza);
		}
		else if (input == "4") {
			clear();
			clear();
			try {
				vector<string> names;
				for (size_t i = 0; i < pizzas.size(); ++i) {
					names.push_back("Pizza with " + to_string(pizzas.at(i).getToppings().size()) + " toppings");
				}
				names.push_back("Back");
				printMenu(names, "Current Pizzas");
				getInput(input);
				int index = service.convertStringToInt(input);
				if (index == names.size()) {
					clear();
				}
				else {
					try {
						pizzas = service.deleteItem(pizzas, index - 1);
						clear();
						printMessage("Pizza removed.");
					}
					catch (out_of_range) {
						clear();
						printMessage("Not a valid option.");
					}
				}
			}
			catch (EmptyVector) {
				clear();
				printMessage("No pizzas available.");
			}
		}
		else if (input == "5") {
			clear();
			try {
				vector<string> names = service.getNames<SideOrder>();
				names.push_back("Back");
				printMenu(names, "Sides");
				getInput(input);
				int index = service.convertStringToInt(input);
				if (index == names.size()) {
					clear();
				}
				else {
					try {
						sides.push_back(service.getItem<SideOrder>(index - 1));
						clear();
						printMessage("Side added.");
					}
					catch (out_of_range) {
						clear();
						printMessage("Not a valid option.");
					}
				}
			}
			catch (EmptyVector) {
				clear();
				printMessage("No toppings available.");
			}
		}
		else if (input == "6") {
			clear();
			try {
				vector<string> names = service.getNames(sides);
				names.push_back("Back");
				printMenu(names, "Current Sides");
				getInput(input);
				int index = service.convertStringToInt(input);
				if (index == names.size()) {
					clear();
				}
				else {
					try {
						sides = service.deleteItem(sides, index - 1);
						clear();
						printMessage("Side removed.");
					}
					catch (out_of_range) {
						clear();
						printMessage("Not a valid option.");
					}
				}
			}
			catch (EmptyVector) {
				clear();
				printMessage("No sides available.");
			}
		}
		else if (input == "7") {
			clear();
			Order order;
			order.setPizzas(pizzas);
			order.setSides(sides);
			offer.setOrder(order);
			//Validate stuff
			service.addItem<Offer>(offer);
			clear();
			printMessage("Offer completed.");
			return;
		}
		else if (input == "8") {
			clear();
			printMessage("Offer canceled.");
			return;
		}

		else {
			clear();
			printMessage("Not a valid option.");
		}
	}
}

void ManagerUI::showOfferViewMenu() {
	string input;
	try {
		while (true) {
			vector<Offer> offers = service.getItems<Offer>();
			vector<string> names = service.getNames<Offer>();
			names.push_back("Back");
			printMenu(names, "Offers");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size()) {
				clear();
				return;
			}
			else {
				clear();
				printMessage("Not a valid option.");
			}
		}
	}
	catch (EmptyVector) {
		clear();
		printMessage("There are currently no toppings.");
	}
}

void ManagerUI::showOfferDeleteMenu() {
	string input;
	try {
		while (true) {
			vector<string> names = service.getNames<Offer>();
			names.push_back("Back");
			printMenu(names, "Offers");
			getInput(input);
			int index = service.convertStringToInt(input);
			if (index == names.size()) {
				clear();
				return;
			}
			else {
				try {
					service.deleteItem<Offer>(index - 1);
					clear();
					printMessage("Topping deleted.");
				}
				catch (out_of_range) {
					clear();
					printMessage("Not a valid option.");
				}
			}
		}
	}
	catch (EmptyVector) {
		clear();
		printMessage("There are currently no toppings.");
	}
}

void ManagerUI::showCreatePizzaMenu(Pizza& pizza) {
	string input;
	while (true) {
		printMenu({ "Add Topping", "Remove Topping", "Set Crust", "Set Size", "Complete", "Cancel" }, "Pizza Creator");
		getInput(input);
		if (input == "1") {
			clear();
			try {
				vector<string> names = service.getNames<Topping>();
				names.push_back("Any Topping");
				names.push_back("Back");
				printMenu(names, "Toppings");
				getInput(input);
				int index = service.convertStringToInt(input);
				if (index == names.size()) {
					clear();
				}
				else if (index == names.size() - 1) {
					pizza.addToppings(Topping("Any Topping", 0));
					clear();
					printMessage("Topping added.");
				}
				else {
					try {
						pizza.addToppings(service.getItem<Topping>(index - 1));
						clear();
						printMessage("Topping added.");
					}
					catch (out_of_range) {
						clear();
						printMessage("Not a valid option.");
					}
				}
			}
			catch (EmptyVector) {
				clear();
				printMessage("No toppings available.");
			}
		}
		else if (input == "2") {
			clear();
			try {
				vector<string> names = service.getNames(pizza.getToppings());
				names.push_back("Back");
				printMenu(names, "Toppings");
				getInput(input);
				int index = service.convertStringToInt(input);
				if (index == names.size()) {
					clear();
				}
				else {
					try {
						pizza.setToppings(service.deleteItem(pizza.getToppings(), index - 1));
						clear();
						printMessage("Topping removed.");
					}
					catch (out_of_range) {
						clear();
						printMessage("Not a valid option.");
					}
				}
			}
			catch (EmptyVector) {
				clear();
				printMessage("No toppings available.");
			}
		}
		else if (input == "3") {
			clear();
			try {
				vector<string> names = service.getNames<PizzaCrust>();
				names.push_back("Any Crust");
				names.push_back("Back");
				printMenu(names, "Pizza Crusts");
				getInput(input);
				int index = service.convertStringToInt(input);
				if (index == names.size()) {
					clear();
				}
				else if (index == names.size() - 1) {
					pizza.setCrust(PizzaCrust("Any Crust", 0));
					clear();
					printMessage("Crust set.");
				}
				else {
					try {
						pizza.setCrust(service.getItem<PizzaCrust>(index - 1));
						clear();
						printMessage("Crust set.");
					}
					catch (out_of_range) {
						clear();
						printMessage("Not a valid option.");
					}
				}
			}
			catch (EmptyVector) {
				clear();
				printMessage("No toppings available.");
			}
		}
		else if (input == "4") {
			clear();
			try {
				vector<string> names = service.getNames<PizzaSize>();
				names.push_back("Any Size");
				names.push_back("Back");
				printMenu(names, "Pizza Sizes");
				getInput(input);
				int index = service.convertStringToInt(input);
				if (index == names.size()) {
					clear();
				}
				else if (index == names.size() - 1) {
					pizza.setPizzaSize(PizzaSize("Any Size", 0));
					clear();
					printMessage("Size set.");
				}
				else {
					try {
						pizza.setPizzaSize(service.getItem<PizzaSize>(index - 1));
						clear();
						printMessage("Size set.");
					}
					catch (out_of_range) {
						clear();
						printMessage("Not a valid option.");
					}
				}
			}
			catch (EmptyVector) {
				clear();
				printMessage("No toppings available.");
			}
		}
		else if (input == "5") {
			//Validate stuff
			clear();
			printMessage("Pizza created.");
			return;
		}
		else if (input == "6") {
			clear();
			throw 1;
		}
		else {
			clear();
			printMessage("Not a valid option.");
		}
	}
}