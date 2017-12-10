#include "ManagerUI.h"
//TODO: Fix comment on the bottom and make this code more readable.

ManagerUI::ManagerUI() {
}

void ManagerUI::managerMenu() {
	while (true) {
		cout << menu.printMenu({ "Pizza", "Toppings", "Price", "Locations", "Side orders", "Go Back" }) << endl;
		cout << "Press 'q' to quit.\nWhat would you like to register? ";

		cin.ignore();
		cin >> input;
		system("CLS");

		switch (input)
		{
			case '1':
			{
				//Pizza
				pizzaOption();
				break;
			}
			case '2':
			{
				//Toppings
				toppingOption();
				break;
			}
			case '3':
			{
				//Price
				priceOption();
				break;
			}
			case '4':
			{
				//Location
				locationOption();
				break;
			}
			case '5':
				//Side orders
				sideOrderOption();
				break;
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
	//TODO: Add options to add sizes/ bottoms   or delete them
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


/*				TOPPINGS			*/

void ManagerUI::validateToppingInput(char input) {
	Data toppingRepo;
	vector <Topping> toppings = toppingRepo.RetrieveAllFromFile<Topping>();
	Topping topping;

	switch (input) {
	case '1': {
		//Adding a topping
		addMultipleToppings();
		break;
	}
	case '2': {
		//Delete a topping
		if (toppings.size() != 0) {
			deleteToppings();
		}
		else cout << "You have no toppings so far." << endl;
		break;
	}
	case '3': {
		//See all toppings
		if (toppings.size() != 0) {
			seeAllToppings();
		}
		else cout << "You have no toppings so far." << endl;
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
	seeAllToppings();
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
	seeAllToppings();
	cout << "What topping would you like to delete. Please input a number: " << endl;
	cout << "Input: ";
	cin >> input;
	//Changing the input from char to int
	int inputInInt = (int)input - 49;
	service.deleteTopping(inputInInt);
}


void ManagerUI::seeAllToppings() {
	Data toppingRepo;
	vector <Topping> toppings = toppingRepo.RetrieveAllFromFile<Topping>();
	Topping topping;
	cout << "Here are the toppings you have so far: " << endl;
	for (unsigned int i = 0; i < toppings.size(); i++) {
		cout << i + 1 << ": " << toppings.at(i) << endl;
	}
}



/*				LOCATIONS			*/


void ManagerUI::validateLocationOptions(char input) {
	Data locationRepo;
	vector<Location> locations = service.getLocations();
	Location location;
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
		if (locations.size() != 0) {
			addingMultipleLocations();
		}
		else cout << "You have no locations so far." << endl;
		break;
	}
	case '3': {
		//See all locations
		if (locations.size() != 0) {
			seeAllLocations();
		}
		else cout << "You have no locations so far." << endl;
		system("PAUSE");
		break;
	}
	}
}


void ManagerUI::addingMultipleLocations() {
	int numberOfLocations;
	Data locationRepo;
	vector<Location> locations = service.getLocations();
	Location location;
	seeAllLocations();
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
	seeAllLocations();
	cout << "What location would you like to delete. Please input a number: " << endl;
	cout << "Input: ";
	cin >> input;
	//Changing the input from char to int
	int inputInInt = (int)input - 49;
	service.deleteLocation(inputInInt);
}


void ManagerUI::seeAllLocations() {
	Data locationRepo;
	vector<Location> locations = service.getLocations();
	Location location;
	cout << "Here are the locations you have so far: " << endl;
	for (unsigned int i = 0; i < locations.size(); i++) {
		cout << i + 1 << ": " << locations.at(i).getAddress() << endl;
	}
}


/*			SIDE ORDERS		*/

void ManagerUI::validateOtherInput(char input) {
	Data sideOrderRepo;
	vector <SideOrder> sides = sideOrderRepo.RetrieveAllFromFile<SideOrder>();
	SideOrder sideOrder;
	switch (input) {
	case '1': {
		//Add a side order
		seeAllSides();
		addMultipleSides();
		break;
	}
	case '2': {
		//delete a side order
		if (sides.size() != 0) {
			seeAllSides();
			deleteMultipleSides();
		}
		else cout << "You have no side orders so far." << endl;
		break;
	}
	case '3': {
		//See all side orders
		if (sides.size() != 0) {
			seeAllSides();
		}
		else cout << "You have no side orders so far." << endl;
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
	Data sideOrderRepo;
	vector <SideOrder> sides = sideOrderRepo.RetrieveAllFromFile<SideOrder>();
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
	cout << "What topping would you like to delete. Please input a number: " << endl;
	cout << "Input: ";
	cin >> input;
	//Changing the input from char to int
	int inputInInt = (int)input - 49;
	service.deleteSideOrder(inputInInt);
}


void ManagerUI::seeAllSides() {
	Data sideOrderRepo;
	vector <SideOrder> sides = sideOrderRepo.RetrieveAllFromFile<SideOrder>();
	SideOrder sideOrder;
	cout << "Here are the side orders you have so far: " << endl;
	for (unsigned int i = 0; i < sides.size(); i++) {
		cout << i + 1 << ": " << sides.at(i) << endl;
	}
}
