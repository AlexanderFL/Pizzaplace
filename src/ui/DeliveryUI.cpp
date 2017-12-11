#include "DeliveryUI.h"
#include "Order.h"
#include "Menu.h"

//TODO: Fix home address! 

DeliveryUI::DeliveryUI()
{
	ignore = true;
}

void DeliveryUI::setIgnore(bool ignore) {
	this-> ignore = ignore;
}

void DeliveryUI::deliveryMenu() {
	char input;
	Menu menu;
	while (true) {
		cout << menu.printMenu({ "Dislpay Orders", "Display Orders at location", "Go Back" }) << endl;
		cin >> input;
		switch (input)
		{
		case '1': {
			allOrdersMenu();
			break;
		}
		case '2': {
			ordersMenu();
			break;
		}
		case '3': {
			return;
		}
		default:
			cout << "Invalid input." << endl;
			break;
		}
	}
}

void DeliveryUI::allOrdersMenu() {
	char input;
	try {
		vector<Order> orders = service.getOrders();
		for (size_t i = 0; i < orders.size(); ++i) {
			cout << i + 1 << ": " << orders.at(i).getStatus() << endl;
		}
		cout << "Input: ";
		cin >> input;
		try {
			int order = (int)input - 49;
			cout << orders.at(order) << endl;
			cout << "1: Set as paid" << endl;
			cout << "2: Set as delivered" << endl;
			cout << "3: Go back" << endl;
			cout << "Input: " << endl;
			cin >> input;
			switch (input) {
			case '1': {
				try {
					service.setOrderPaid(orders.at(order).getID());
				}
				catch (out_of_range) {
					cout << "Invalid index." << endl;
				}
				break;
			}
			case '2': {
				try {
					service.setOrderDelivered(orders.at(order).getID());
				}
				catch (out_of_range) {
					cout << "Invalid index." << endl;
				}
				break;
			}
			case '3': {
				return;
			}
			default:
				cout << "Invalid input." << endl;
				break;
			}
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
	char input;
	try {
		vector<Location> locations = service.getLocations();
		cout << "Choose the location of your workplace" << endl;
		for (size_t i = 0; i < locations.size(); ++i) {
			cout << i + 1 << ": " << locations.at(i).getAddress() << endl;
		}
		cout << "Input: ";
		cin >> input;
		try {
			vector<Order> orders = service.getOrders(locations.at((int)input - 49));
			for (size_t i = 0; i < orders.size(); ++i) {
				cout << i + 1 << ": " << showOrderInfoShort(orders.at(i)) << endl;
			}
			cout << "Input: ";
			cin >> input;
			try {
				int order = (int)input - 49;
				cout << showOrderInfo(orders.at(order)) << endl;
				cout << "Set as paid" << endl;
				cout << "Set as delivered" << endl;
				cout << "Go back" << endl;
				cout << "Input: " << endl;
				switch (input) {
				case '1': {
					try {
						service.setOrderPaid(orders.at(order).getID());
					}
					catch (out_of_range) {
						cout << "Invalid index." << endl;
					}
					break;
				}
				case '2': {
					try {
						service.setOrderDelivered(orders.at(order).getID());
					}
					catch (out_of_range) {
						cout << "Invalid index." << endl;
					}
					break;
				}
				case '3': {
					return;
				}
				default:
					cout << "Invalid input." << endl;
					break;
				}
			}
			catch (out_of_range) {
				cout << "Invalid index." << endl;
			}
		}
		catch (out_of_range) {
			cout << "Invalid index" << endl;
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
	info += pizza.getCrust().getName() + " pizza - ";
	if (pizza.getPhase() == PREPERATION) {
		info += "in preperation";
	}
	else if (pizza.getPhase() == BAKING) {
		info += "baking";
	}
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
	info += "Paid: ";
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
		info += " needs to be picked up";
	}
	return info;
}