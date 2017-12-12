#include "ManagerUI.h"

ManagerUI::ManagerUI() {
}

void ManagerUI::managerMenu() {
	while (true) {
		cout << menu.printMenu({ "Pizza", "Toppings", "Locations", "Side orders", "Menu options", "Go Back" }) << endl;
		cout << "Press 'q' to quit.\nWhat would you like to register? ";

		cin.ignore();
		cin >> input;
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
	//TODO: Add options to add sizes/bottoms/crust or delete them
	while (true) {
		cout << menu.printMenu({ "Size", "Bottom / Crust", "Go Back" }) << endl;
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
		cout << menu.printMenu({ "Add a crust", "Delete a crust", "See all crusts available", "Go Back" }) << endl;
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
	vector<PizzaCrust> crusts = service.getAll<PizzaCrust>();
	char input;
	cout << "\nPlease input a number: ";
	cin >> input;
	int inputInInt = (int)input - 49;
	service.deleteItem<PizzaCrust>(inputInInt);
}

void ManagerUI::seeAllCrust() {
	vector <PizzaCrust> crusts = service.getAll<PizzaCrust>();
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
	cout << menu.printMenu({ "Add a new Size", "Delete a Size", "See all Sizes", "Go back" }) << endl;
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
	seeAllSizesMenu();
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
	char input;
	cin >> input;
	int inputInInt = (int)input - 49;
	service.deleteItem<PizzaSize>(inputInInt);
}

void ManagerUI::seeAllSizesMenu() {
	vector<PizzaSize> sizes = service.getAll<PizzaSize>();
	for (size_t i = 0; i < sizes.size(); ++i) {
		cout << "Crust " << i + 1 << ": " << sizes.at(i).getName() << " - " << sizes.at(i).getPriceMod() << " Kr.";
	}
	cout << endl;
}

void ManagerUI::toppingOption() {
	while (true) {
		cout << menu.printMenu({ "Add a topping", "Delete a topping", "See all toppings", "Go Back" }) << endl;
		cout << "Input: ";
		cin >> input;
		system("CLS");
		validateToppingInput(input);
		if (input == '4') return;
	}
}

void ManagerUI::locationOption() {
	while (true) {
		cout << menu.printMenu({ "Add a location", "Remove a location", "See all Locations", "Go Back" }) << endl;
		cout << "What would you like to do? ";
		cin >> input;
		validateLocationOptions(input);
		if (input == '4') return;
	}	
}

void ManagerUI::sideOrderOption() {
	while(true){
		cout << menu.printMenu({ "Add a side order", "delete a side order",  "See all side orders", "Go Back" }) << endl;
		cout << "Input: ";
		cin >> input;
		system("CLS");
		validateOtherInput(input);
		if (input == '4') return;
	}
}

void ManagerUI::pizzaMenuOption() {
	while (true) {
		cout << menu.printMenu({ "Add a pizza", "Remove a pizza", "Pizza menu", "Go Back" }) << endl;
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
	if ((service.getAll<Topping>()).size() != 0) {
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
	vector <Topping> toppings = service.getAll<Topping>();
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
	vector<Location> locations = service.getAll<Location>();
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
	if ((service.getAll<Location>()).size() != 0) {
		cout << "What location would you like to delete. Please input a number: " << endl;
		cout << "Input: ";
		cin >> input;
		//Changing the input from char to int
		int inputInInt = (int)input - 49;
		service.deleteItem<Location>(inputInInt);
	}
}

void ManagerUI::seeAllLocations() {
	vector<Location> locations = service.getAll<Location>();
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
	if ((service.getAll<SideOrder>()).size() != 0) {
		cout << "What topping would you like to delete. Please input a number: " << endl;
		cout << "Input: ";
		cin >> input;
		//Changing the input from char to int
		int inputInInt = (int)input - 49;
		service.deleteItem<SideOrder>(inputInInt);
	}
}


void ManagerUI::seeAllSides() {
	vector <SideOrder> sides = service.getAll<SideOrder>();
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
			vector <Topping> toppings = service.getAll<Topping>();
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
	vector <Offer> offers = service.getAll<Offer>();
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
	if ((service.getAll<Offer>()).size() != 0) {
		cout << "What offer would you like to delete. Please input a number: " << endl;
		cout << "Input: ";
		cin >> input;
		//Changing the input from char to int
		int inputInInt = (int)input - 49;
		service.deleteItem<Offer>(inputInInt);
	}
}