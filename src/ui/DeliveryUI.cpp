#include "DeliveryUI.h"
#include "Order.h"
#include "CommonUI.h"

//TODO: Fix home address! 

DeliveryUI::DeliveryUI() {}

void DeliveryUI::deliveryMenu() {
	string input;
	while (true) {
		cout << printMenu({ "Dislpay Orders", "Display Orders at location", "Go Back" }) << endl;
		cout << "Input: ";
		cin >> ws;
		getline(cin, input);
		if (input == "1") {
			allOrdersMenu();
		}
		else if (input == "2") {
			ordersMenu();
		}
		else if (input == "3") {
			return;
		}
		else {
			cout << "Invalid input." << endl;
		}
	}
}

void DeliveryUI::allOrdersMenu() {
	string input;
	try {
		vector<Order> orders = service.getOrders();
		cout << "Select an option" << endl;
		for (size_t i = 0; i < orders.size(); ++i) {
			cout << i + 1 << ": ";
			showOrderInfoShort(orders.at(i));
		}
		cout << "Input: ";
		cin >> ws;
		getline(cin, input);
		try {
			int order = service.convertStringToInt(input) - 1;
			showOrderInfo(orders.at(order));
			cout << "1: Set as paid" << endl;
			cout << "2: Set as delivered" << endl;
			cout << "3: Go back" << endl;
			cout << "Input: " << endl;
			cin >> ws;
			getline(cin, input);
			if (input == "1") {
				try {
					service.setOrderPaid(orders.at(order).getID());
				}
				catch (out_of_range) {
					cout << "Invalid index." << endl;
				}
			}
			else if (input == "2") {
				try {
					service.setOrderDelivered(orders.at(order).getID());
				}
				catch (out_of_range) {
					cout << "Invalid index." << endl;
				}
			}
			else if (input == "3") {
				return;
			}
			else {
				cout << "Invalid input." << endl;
			}
		}
		catch (InvalidString) {
			cout << "Invalid input." << endl;
		}
		catch (out_of_range) {
			cout << "Invalid index." << endl;
		}
	}
	catch (EmptyVector) {
		cout << "No orders availabe." << endl;
	}
	catch (FailedOpenFile) {
		cout << "Failed to open file." << endl;
	}
}

void DeliveryUI::ordersMenu() {
	string input;
	try {
		vector<Location> locations = service.getLocations();
		cout << "Choose the location of your workplace" << endl;
		for (size_t i = 0; i < locations.size(); ++i) {
			cout << i + 1 << ": " << locations.at(i).getAddress() << endl;
		}
		cout << "Input: ";
		cin >> ws;
		getline(cin, input);
		try {
			int index = service.convertStringToInt(input) - 1;
			vector<Order> orders = service.getOrders(locations.at(index));
			for (size_t i = 0; i < orders.size(); ++i) {
				cout << i + 1 << ": ";
				showOrderInfoShort(orders.at(i));
			}
			cout << "Input: ";
			cin >> ws;
			getline(cin, input);
			int order = service.convertStringToInt(input) - 1;
			try {
				showOrderInfo(orders.at(order));
				cout << "1: Set as paid" << endl;
				cout << "2: Set as delivered" << endl;
				cout << "3: Go back" << endl;
				cout << "Input: ";
				cin >> ws;
				getline(cin, input);
				if (input == "1") {
					try {
						service.setOrderPaid(orders.at(order).getID());
					}
					catch (out_of_range) {
						cout << "Invalid index." << endl;
					}
				}
				if(input == "2") {
					try {
						service.setOrderPaid(orders.at(order).getID());
						service.setOrderDelivered(orders.at(order).getID());
					}
					catch (out_of_range) {
						cout << "Invalid index." << endl;
					}
				}
				if (input == "3") {
					return;
				}
				else {
					cout << "Invalid input." << endl;
				}
			}
			catch (InvalidString) {
				cout << "Invalid input." << endl;
			}
			catch (out_of_range) {
				cout << "Invalid index." << endl;
			}
		}
		catch (InvalidString) {
			cout << "Invalid input." << endl;
		}
		catch (out_of_range) {
			cout << "Invalid index." << endl;
		}
		catch (EmptyVector) {
			cout << "No orders available for this location." << endl;
		}
		catch (FailedOpenFile) {
			cout << "Failed to open file." << endl;
		}
	}
	catch (EmptyVector) {
		cout << "No locations available." << endl;
	}
	catch (FailedOpenFile) {
		cout << "Failed to open file." << endl;
	}
}

void DeliveryUI::showPizzaInfoShort(const Pizza& pizza) const {
	cout << pizza.getToppings().size() << " toppings, ";
	cout << pizza.getPizzaSize().getName() << " ";
	cout << pizza.getCrust().getName() << " pizza.";
}

void DeliveryUI::showOrderInfo(const Order& order) const {
	cout << "Order: " << order.getID() << endl << "Pizzas: ";
	if (order.getPizzas().size() == 0) {
		cout << "None";
	}
	else {
		cout << endl;
		for (size_t i = 0; i < order.getPizzas().size(); ++i) {
			cout << "\tPizza " << i + 1 << ": ";
			showPizzaInfoShort(order.getPizzas().at(i));
		}
		
	}
	cout << endl << "Side Orders: ";
	if (order.getSides().size() == 0) {
		cout <<"None";
	}
	else {
		cout << endl;
		for (size_t i = 0; i < order.getSides().size(); ++i) {
			cout << "\t";
			cout << order.getSides().at(i).getName();
		}
	}
	cout << endl << "Comment: " + order.getComment() << endl;
	cout << "Location: " + order.getLocation().getAddress() << endl;
	cout << "Delivery Method: ";
	if (order.getDeliveryMethod() == PICKUP) {
		cout << "Pickup" << endl;
	}
	else if (order.getDeliveryMethod() == SEND) {
		cout << "Send to " << order.getHomeAddress() << endl;
	}
	cout << "Paid: ";
	if (order.isPaidFor()) {
		cout << "True";
	}
	else {
		cout << "False";
	}
	cout << endl;
}

void DeliveryUI::showOrderInfoShort(const Order& order) const {
	cout << "Order " << order.getID() << " - ";
	cout <<  order.getPizzas().size() << " pizzas, ";
	cout << order.getSides().size() << " side orders, ";
	if (order.isPaidFor()) {
		cout << "paid, ";
	}
	else {
		cout <<  "unpaid, ";
	}
	if (order.getDeliveryMethod() == SEND) {
		cout << "needs to be sent";
	}
	else {
		cout << "awaiting pickup";
	}
	cout << endl;
}