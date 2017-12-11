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
				cout << i + 1 << ": " << orders.at(i).getStatus() << endl;
			}
			cout << "Input: ";
			cin >> input;
			try {
				int order = (int)input - 49;
				cout << orders.at(order) << endl;
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