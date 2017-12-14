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
			printMenu(names, "Locations");
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
			printMenu(names, "Pizza sizes");
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
			showSCrustDeleteMenu();
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


void ManagerUI::showSCrustDeleteMenu() {
	string input;
	try {
		while(true){
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
		}
		else if (input == "3") {
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
		service.addItem<PizzaCrust>(PizzaCrust(name, priceInInt));
		clear();
		printMessage("Pizza side was created.");
	}
	catch (InvalidString) {
		clear();
		printMessage("Invalid input.");
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



/*OLD MENU*/

void ManagerUI::managerMenu() {
	while (true) {
		printMenu({ "Pizza", "Toppings", "Locations", "Side orders", "Menu options", "Go Back" });
		cout << endl;
		cout << "Press 'q' to quit.\nWhat would you like to register? ";

		cin >> input;
		cin.ignore();
		system("CLS");
		switch (input)
		{
			case '1':{
				//Pizza
				pizzaOption();
				break;
			}
			case '2':{
				//Toppings
				toppingOption();
				break;
			}
			case '3':{
				//Location
				locationOption();
				break;
			}
			case '4':
				//Side orders
				sideOrderOption();
				break;
			case '5':
				//Pizza Menu
				pizzaMenuOption();
			case '6':
				//Go back
				return;
			case 'q':
			case 'Q':
				exit(1);
			default:
				cout << "Not a valid option." << endl;
		}
	}
}

/*			OPTIONS AVAILABLE			*/	

void ManagerUI::pizzaOption() {
	while (true) {
		printMenu({ "Size", "Bottom / Crust", "Go Back" });
		cout << endl;
		cout << "Press 'q' to quit.\nWhat would you like to register? ";
		cin >> input;
		if (input == '3') break;
		switch (input) {
		case '1':
			//Size
			validateSizeOptions();
			break;
		case '2':
			//Crust
			validateCrustOptions();
			break;
		default:
			cout << "Invalid input" << endl;
		}
	}
}

void ManagerUI::validateCrustOptions() {
	char input;
	while (true) {
		printMenu({ "Add a crust", "Delete a crust", "See all crusts available", "Go Back" });
		cout << endl;
		cout << "Input: ";
		cin >> input;
		system("CLS");
		validateCrustInput(input);
		if (input == '4') return;
	}
}

void ManagerUI::validateCrustInput(char input) {
	switch (input) {
	case '1': {
		//Adding a crust
		addingMultipleCrusts();
		break;
	}
	case '2': {
		//Delete a crust
		deleteMultipleCrusts();
		break;
	}
	case '3': {
		//See all crust options
		seeAllCrust();
		system("PAUSE");
		break;
	}
	case '4': {
		//Go back
		break;
	}
	default: {
		cout << "Invalid input." << endl;
		break;
		}
	}
}

void ManagerUI::addingMultipleCrusts() {
	seeAllCrust();
	int numberOfCrusts;
	PizzaCrust crust;
	cout << "How many crusts would you like to add? ";
	cin >> numberOfCrusts;
	cout << "What would you like as a crust? " << endl;

	for (int i = 0; i < numberOfCrusts; ++i) {
		cout << "crust number " << i + 1 << ": ";
		cin >> crust;
		service.addCrust(crust);
	}
}

void ManagerUI::deleteMultipleCrusts() {
	seeAllCrust();
	vector<PizzaCrust> crusts = service.getItems<PizzaCrust>();
	char input;
	cout << "\nPlease input a number: ";
	cin >> input;
	int inputInInt = (int)input - 49;
	service.deleteItem<PizzaCrust>(inputInInt);
}

void ManagerUI::seeAllCrust() {
	vector <PizzaCrust> crusts = service.getItems<PizzaCrust>();
	if (crusts.size() != 0) {
		cout << "Here are the crusts you have so far: " << endl;
		for (unsigned int i = 0; i < crusts.size(); i++) {
			cout << i + 1 << ": " << crusts.at(i) << endl;
		}
	}
	else {
		cout << "You have no crusts so far." << endl;
	}
}

void ManagerUI::validateSizeOptions() {
	printMenu({ "Add a new Size", "Delete a Size", "See all Sizes", "Go back" });
	cout << endl;
	cout << "Input: ";
	cin >> input;
	switch (input) {
	case '1': {
		//Adding a size
		addSizeMenu();
		break;
	}
	case '2': {
		//Delete a size
		deleteSizeMenu();
		break;
	}
	case '3': {
		//See all size
		seeAllSizesMenu();
		system("PAUSE");
		break;
	}
	case '4': {
		//Go back
		break;
	}
	default: {
		cout << "Invalid input." << endl;
		break;
		}
	}
}

void ManagerUI::addSizeMenu() {
	try {
		seeAllSizesMenu();
	}
	catch (EmptyVector) {
		cout << "There are currently no toppings." << endl;
	}
	string name;
	double mod;
	cout << "Name of the new size: ";
	cin >> ws;
	getline(cin, name);
	cout << "Price modifier of the new size: ";
	cin >> mod;
	service.addItem(PizzaSize(name, mod));
}

void ManagerUI::deleteSizeMenu() {
	seeAllSizesMenu();
	cout << "Input: ";
	char input;
	cin >> input;
	int inputInInt = (int)input - 49;
	try {
		service.deleteItem<PizzaSize>(inputInInt);
	}
	catch (out_of_range) {
		cout << "Invalid index." << endl;
	}
}

void ManagerUI::seeAllSizesMenu() {
	vector<PizzaSize> sizes = service.getItems<PizzaSize>();
	for (size_t i = 0; i < sizes.size(); ++i) {
		cout << "Crust " << i + 1 << ": " << sizes.at(i).getName() << " - " << (sizes.at(i).getPriceMod() - 1)*100 << " %";
	}
	cout << endl;
}

void ManagerUI::toppingOption() {
	while (true) {
		printMenu({ "Add a topping", "Delete a topping", "See all toppings", "Go Back" });
		cout << endl;
		cout << "Input: ";
		cin >> input;
		system("CLS");
		validateToppingInput(input);
		if (input == '4') return;
	}
}

void ManagerUI::locationOption() {
	while (true) {
		printMenu({ "Add a location", "Remove a location", "See all Locations", "Go Back" });
		cout << endl;
		cout << "What would you like to do? ";
		cin >> input;
		validateLocationOptions(input);
		if (input == '4') return;
	}	
}

void ManagerUI::sideOrderOption() {
	while(true){
		printMenu({ "Add a side order", "delete a side order",  "See all side orders", "Go Back" });
		cout << endl;
		cout << "Input: ";
		cin >> input;
		system("CLS");
		validateOtherInput(input);
		if (input == '4') return;
	}
}

void ManagerUI::pizzaMenuOption() {
	while (true) {
		printMenu({ "Add a pizza", "Remove a pizza", "Pizza menu", "Go Back" });
		cout << endl;
		cout << "What would you like to do? ";
		cin >> input;
		validatePizzaMenuOption(input);
		if (input == '4') return;
	}
}


/*				TOPPINGS			*/

void ManagerUI::validateToppingInput(char input) {
	switch (input) {
	case '1': {
		//Adding a topping
		addMultipleToppings();
		break;
	}
	case '2': {
		//Delete a topping
		deleteToppings();
		break;
	}
	case '3': {
		//See all toppings
		seeAllToppings();
		system("PAUSE");
		break;
	}
	case '4': {
		//Go back
		break;
	}
	default: {
		cout << "Invalid input." << endl;
		break;
	}
	}
}

void ManagerUI::addMultipleToppings() {
	int numberOfToppings;
	Topping topping;
	cout << "How many toppings would you like to add? ";
	cin >> numberOfToppings;
	cout << "What would you like as a topping? " << endl;

	for (int i = 0; i < numberOfToppings; ++i) {
		cout << "Topping number " << i + 1 << ": ";
		cin >> topping;
		service.addTopping(topping);
	}
}

void ManagerUI::deleteToppings() {
	char input;
	if ((service.getItems<Topping>()).size() != 0) {
		seeAllToppings();
		cout << "What topping would you like to delete. Please input a number: " << endl;
		cout << "Input: ";
		cin >> input;
		//Changing the input from char to int
		int inputInInt = (int)input - 49;
		service.deleteItem<Topping>(inputInInt);
	}
}


void ManagerUI::seeAllToppings() {
	vector <Topping> toppings = service.getItems<Topping>();
	if (toppings.size() != 0) {
		cout << "Here are the toppings you have so far: " << endl;
		for (unsigned int i = 0; i < toppings.size(); i++) {
			cout << i + 1 << ": " << toppings.at(i) << endl;
		}
	}
	else {
		cout << "You have no toppings so far." << endl;
	}
}

/*				LOCATIONS			*/

void ManagerUI::validateLocationOptions(char input) {
	seeAllLocations();
	switch (input) {
	case '1':
	{
		//Adding a location
		addingMultipleLocations();
		break;
	}
	case '2':
	{
		//Delete a Location
		deleteMultipleLocations();
		break;
	}
	case '3': {
		//See all locations
		seeAllLocations();
		system("PAUSE");
		break;
		}
	}
}

void ManagerUI::addingMultipleLocations() {
	int numberOfLocations;
	vector<Location> locations = service.getItems<Location>();
	Location location;
	cout << "How many locations would you like to add? ";
	cin >> numberOfLocations;
	cout << "Where would you like the locatins to be? " << endl;

	for (int i = 0; i < numberOfLocations; ++i) {
		cout << "location number " << i + 1 << ": ";
		cin >> location;
		service.addLocation(location);
	}
}

void ManagerUI::deleteMultipleLocations() {
	char input;
	if ((service.getItems<Location>()).size() != 0) {
		cout << "What location would you like to delete. Please input a number: " << endl;
		cout << "Input: ";
		cin >> input;
		//Changing the input from char to int
		int inputInInt = (int)input - 49;
		service.deleteItem<Location>(inputInInt);
	}
}

void ManagerUI::seeAllLocations() {
	vector<Location> locations = service.getItems<Location>();
	if (locations.size() != 0) {
		cout << "Here are the locations you have so far: " << endl;
		for (unsigned int i = 0; i < locations.size(); i++) {
			cout << i + 1 << ": " << locations.at(i).getAddress() << endl;
		}
	}
	else {
		cout << "You have no locations so far." << endl;
	}
}

/*			SIDE ORDERS		*/

void ManagerUI::validateOtherInput(char input) {
	seeAllSides();
	switch (input) {
	case '1': {
		//Add a side order
		addMultipleSides();
		break;
	}
	case '2': {
		//delete a side order
		deleteMultipleSides();
		break;
	}
	case '3': {
		//See all side orders
		seeAllSides();
		break;
	}
	case '4': {
		//go back
		break;
	}
	default:
		cout << "Invalid input." << endl;
		break;
	}
}

void ManagerUI::addMultipleSides() {
	int numberOfSides;
	SideOrder sideOrder;
	cout << "How many side orders would you like to add? ";
	cin >> numberOfSides;
	cout << "What would you like as a side order? " << endl;

	for (int i = 0; i < numberOfSides; ++i) {
		cout << "Side number " << i + 1 << ": ";
		cin >> sideOrder;
		service.addSideOrder(sideOrder);
	}
}

void ManagerUI::deleteMultipleSides() {
	char input;
	if ((service.getItems<SideOrder>()).size() != 0) {
		cout << "What topping would you like to delete. Please input a number: " << endl;
		cout << "Input: ";
		cin >> input;
		//Changing the input from char to int
		int inputInInt = (int)input - 49;
		service.deleteItem<SideOrder>(inputInInt);
	}
}


void ManagerUI::seeAllSides() {
	vector <SideOrder> sides = service.getItems<SideOrder>();
	if (sides.size() != 0) {
		cout << "Here are the side orders you have so far: " << endl;
		for (unsigned int i = 0; i < sides.size(); i++) {
			cout << i + 1 << ": " << sides.at(i) << endl;
		}
	}
	else {
		cout << "You have no Sides so far." << endl;
	}
}

/*			PIZZA MENU			*/	

void ManagerUI::validatePizzaMenuOption(char input) {
	switch (input) {
	case '1': {
		//Add a Pizza/Offer to the menu
		addMultiplePizza();
		break;
	}
	case '2': {
		//delete a Pizza from the menu
		deletePizzaOnMenu();
		break;
	}
	case '3': {
		seePizzaMenu();
		break;
	}
	case '4': {
		//go back
		break;
	}
	default:
		cout << "Invalid input." << endl;
		break;
	}
}

void ManagerUI::addMultiplePizza() {
	int numberOfPizzas;
	Offer offer;
	//seePizzaMenu();
	cout << "How many pizza offers would you like to add? ";
	cin >> numberOfPizzas;
	cout << "What would you like as a pizza offer? " << endl << endl;
	for (int i = 0; i < numberOfPizzas; ++i) {
		vector<Pizza> pizza;
		vector<Topping> tops;
		cout << "Pizza number " << i + 1 << ": ";
		cin >> offer;
		char numOfToppings;
		cout << "How many toppings would you like on this pizza? ";
		cin >> numOfToppings;
		int inputInInt = (int)numOfToppings - 48;
		seeAllToppings();
		cout << "Please pick on of those. Input: ";
		for (int i = 0; i < inputInInt; i++) {
			vector <Topping> toppings = service.getItems<Topping>();
			char toppingID;
			cin >> toppingID;
			tops.push_back(toppings.at((int)toppingID - 49));
		}
		pizza.push_back(Pizza(offer.getName(), tops, offer.getPrice()));
		Order order;
		order.setPizzas(pizza);
		offer.setOrder(order);
		service.addOffer(offer);
	}
}

void ManagerUI::seePizzaMenu() {
	vector <Offer> offers = service.getItems<Offer>();
	if (offers.size() != 0) {
		cout << "Here are the offers you have so far: " << endl;
		for (unsigned int i = 0; i < offers.size(); i++) {
			cout << endl;
			cout << "Pizzan nr." << i + 1 << ": " << endl;
			cout << offers.at(i);
			cout << "Toppings: ";
			for (unsigned int j = 0; j <offers.at(i).getOrder().getPizzas().size(); j++) {
				cout << offers.at(i).getOrder().getPizzas().at(j) << endl;
			}
		}
	}
	else {
		cout << "You have no pizza offers so far." << endl;
	}
}

void ManagerUI::deletePizzaOnMenu() {
	char input;
	seePizzaMenu();
	if ((service.getItems<Offer>()).size() != 0) {
		cout << "What offer would you like to delete. Please input a number: " << endl;
		cout << "Input: ";
		cin >> input;
		//Changing the input from char to int
		int inputInInt = (int)input - 49;
		service.deleteItem<Offer>(inputInInt);
	}
}