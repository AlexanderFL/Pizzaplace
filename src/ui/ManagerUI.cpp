#include "ManagerUI.h"

ManagerUI::ManagerUI() {
}

void ManagerUI::managerMenu() {
	while (true) {
		cout << menu.printMenu({ "Pizza", "Toppings", "Price", "Locations", "Side orders", "Menu options", "Go Back" }) << endl;
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
				//Price
				priceOption();
				break;
			}
			case '4':{
				//Location
				locationOption();
				break;
			}
			case '5':
				//Side orders
				sideOrderOption();
				break;
			case '6':
				//Pizza Menu
				pizzaMenuOption();
			case '7':
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
	//TODO: Add options to add sizes/ bottoms   or delete them
	while (true) {
		cout << menu.printMenu({ "Size", "Bottom", "Go Back" }) << endl;
		cout << "Press 'q' to quit.\nWhat would you like to register? ";
		cin >> input;
		if (input == '3') break;
	}
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

void ManagerUI::priceOption() {
	//TODO: get the total price of an order
	//Data orderRepo;
	//vector<Order> order;
	//order = orderRepo.RetrieveAllFromFile<Order>();
	//Todo replace with service
	//cout << order.getTotalCost();
	//cout << "The total price of the order is: " << service.getOrderTotalCost(order) << " kr." << endl;
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
	if ((service.getToppings()).size() != 0) {
		seeAllToppings();
		cout << "What topping would you like to delete. Please input a number: " << endl;
		cout << "Input: ";
		cin >> input;
		//Changing the input from char to int
		int inputInInt = (int)input - 49;
		service.deleteTopping(inputInInt);
	}
}


void ManagerUI::seeAllToppings() {
	vector <Topping> toppings = service.getToppings();
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
	vector<Location> locations = service.getLocations();
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
	if ((service.getLocations()).size() != 0) {
		cout << "What location would you like to delete. Please input a number: " << endl;
		cout << "Input: ";
		cin >> input;
		//Changing the input from char to int
		int inputInInt = (int)input - 49;
		service.deleteLocation(inputInInt);
	}
}

void ManagerUI::seeAllLocations() {
	vector<Location> locations = service.getLocations();
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
	if ((service.getSides()).size() != 0) {
		cout << "What topping would you like to delete. Please input a number: " << endl;
		cout << "Input: ";
		cin >> input;
		//Changing the input from char to int
		int inputInInt = (int)input - 49;
		service.deleteSideOrder(inputInInt);
	}
}


void ManagerUI::seeAllSides() {
	vector <SideOrder> sides = service.getSides();
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
	vector<Pizza> pizza;
	seePizzaMenu();
	cout << "How many pizza offers would you like to add? ";
	cin >> numberOfPizzas;
	cout << "What would you like as a pizza offer? " << endl << endl;

	for (int i = 0; i < numberOfPizzas; ++i) {
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
			vector <Topping> toppings = service.getToppings();
			char toppingID;
			cin >> toppingID;
			tops.push_back(toppings.at((int)toppingID - 49));
		}
		pizza.push_back(Pizza(offer.getName(), tops, offer.getPrice()));
	}
	offer.getOrder().setPizzas(pizza);
	service.addOffer(offer);
}


void ManagerUI::seePizzaMenu() {
	vector <Offer> offers = service.getOffers();
	if (offers.size() != 0) {
		cout << "Here are the offers you have so far: " << endl;
		for (unsigned int i = 0; i < offers.size(); i++) {
			cout << "Pizzan nr." << i + 1 << ": " << endl;
			cout << offers.at(i) << endl;
		}
	}
	else {
		cout << "You have no pizza offers so far." << endl;
	}
}