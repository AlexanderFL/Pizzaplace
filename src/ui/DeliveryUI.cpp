#include "DeliveryUI.h"
#include "Order.h"
#include "CommonUI.h"

DeliveryUI::DeliveryUI() {}

void DeliveryUI::deliveryMenu() {
	string input;
	while (true) {
		printMenu({ "Dislpay Orders", "Display Orders at location", "Go Back" }, "Delivery");
		getInput(input);
		clear();
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
			printMessage("Invalid input.");
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
		getInput(input);
		try {
			int order = service.convertStringToInt(input) - 1;
			showOrderInfo(orders.at(order));
			printMenu({ "Set as paid", "Set as delivered", "Go Back" });
			getInput(input);
			if (input == "1") {
				try {
					service.setOrderPaid(orders.at(order).getID());
				}
				catch (out_of_range) {
					printMessage("Invalid input.");
				}
			}
			else if (input == "2") {
				try {
					service.setOrderDelivered(orders.at(order).getID());
				}
				catch (out_of_range) {
					printMessage("Invalid index.");
				}
			}
			else if (input == "3") {
				return;
			}
			else {
				printMessage("Invalid input.");
			}
		}
		catch (InvalidString) {
			printMessage("Invalid input.");
		}
		catch (out_of_range) {
			printMessage("Invalid index.");
		}
	}
	catch (EmptyVector) {
		printMessage("No orders available.");
	}
	catch (FailedOpenFile) {
		printMessage("Failed to open file.");
	}
}

void DeliveryUI::ordersMenu() {
	string input;
	try {
		vector<Location> locations = service.getItems<Location>();
		vector<string> names;
		for (size_t i = 0; i < locations.size(); ++i) {
			names.push_back(locations.at(i).getAddress());
		}
		names.push_back("Back");
		printMenu(names, "Select Location");
		getInput(input);
		try {
			int index = service.convertStringToInt(input) - 1;
			vector<Order> orders = service.getOrders(locations.at(index));
			for (size_t i = 0; i < orders.size(); ++i) {
				cout << i + 1 << ": ";
				showOrderInfoShort(orders.at(i));
			}
			getInput(input);
			int order = service.convertStringToInt(input) - 1;
			try {
				showOrderInfo(orders.at(order));
				//Add the address here
				printMenu({ "Set as paid", "Set as delivered", "Go Back" });
				getInput(input);
				if (input == "1") {
					try {
						service.setOrderPaid(orders.at(order).getID());
					}
					catch (out_of_range) {
						printMessage("Invalid index.");
					}
				}
				if(input == "2") {
					try {
						service.setOrderPaid(orders.at(order).getID());
						service.setOrderDelivered(orders.at(order).getID());
					}
					catch (out_of_range) {
						printMessage("Invalid index.");
					}
				}
				if (input == "3") {
					return;
				}
				else {
					printMessage("Invalid input.");
				}
			}
			catch (InvalidString) {
				printMessage("Invalid input.");
			}
			catch (out_of_range) {
				printMessage("Invalid index.");
			}
		}
		catch (InvalidString) {
			printMessage("Invalid input.");
		}
		catch (out_of_range) {
			printMessage("Invalid index.");
		}
		catch (EmptyVector) {
			printMessage("No orders available for this location");
		}
		catch (FailedOpenFile) {
			printMessage("Failed to open file.");
		}
	}
	catch (EmptyVector) {
		printMessage("No locations available.");
	}
	catch (FailedOpenFile) {
		printMessage("Failed to open file.");
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