#include "DeliveryUI.h"
#include "Order.h"
#include "Menu.h"

//TODO: Fix home address! 

DeliveryUI::DeliveryUI() {}

void DeliveryUI::deliveryMenu() {
	string input;
	Menu menu;
	while (true) {
		cout << menu.printMenu({ "Dislpay Orders", "Display Orders at location", "Go Back" }) << endl;
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
		for (size_t i = 0; i < orders.size(); ++i) {
			cout << i + 1 << ": " << orders.at(i).getStatus() << endl;
		}
		cout << "Input: ";
		cin >> ws;
		getline(cin, input);
		try {
			int order = service.convertStringToInt(input) - 1;
			cout << showOrderInfo(orders.at(order)) << endl;
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
				cout << i + 1 << ": " << showOrderInfoShort(orders.at(i)) << endl;
			}
			cout << "Input: ";
			cin >> ws;
			getline(cin, input);
			int order = service.convertStringToInt(input) - 1;
			try {
				cout << showOrderInfo(orders.at(order)) << endl;
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

string DeliveryUI::showPizzaInfoShort(const Pizza& pizza) const {
	string info = "";
	info += pizza.getID() + " - ";
	info += pizza.getToppings().size() + " toppings, ";
	info += pizza.getPizzaSize().getName() + " ";
	info += pizza.getCrust().getName() + " pizza.";
	return info;
}

string DeliveryUI::showOrderInfo(const Order& order) const {
	string info = "Order: " + order.getID();
	info += "Pizzas: ";
	if (order.getPizzas().size() == 0) {
		info += "None";
	}
	else {
		for (size_t i = 0; i < order.getPizzas().size(); ++i) {
			info += showPizzaInfoShort(order.getPizzas().at(i));
		}
	}
	info += "Side Orders: ";
	if (order.getSides().size() == 0) {
		info += "None";
	}
	else {
		for (size_t i = 0; i < order.getSides().size(); ++i) {
			info += order.getSides().at(i).getName();
		}
	}
	info += "Comment: " + order.getComment();
	info += "Location: " + order.getLocation().getAddress();
	info += "Delivery Method: ";
	if (order.getDeliveryMethod() == PICKUP) {
		info += "Pickup";
	}
	else if (order.getDeliveryMethod() == SEND) {
		info += "Send to " + order.getHomeAddress();
	}
	info += "\nPaid: ";
	if (order.isPaidFor()) {
		info += "True";
	}
	else {
		info += "False";
	}
	return info;
}

string DeliveryUI::showOrderInfoShort(const Order& order) const {
	string info = "";
	info += order.getID() + " - ";
	info += order.getPizzas().size() + " pizzas, ";
	info += order.getSides().size() + " side orders, ";
	if (order.isPaidFor()) {
		info += " paid, ";
	}
	else {
		info += " unpaid, ";
	}
	if (order.getDeliveryMethod() == SEND) {
		info += " needs to be sent";
	}
	else {
		info += " awaiting pickup";
	}
	return info;
}