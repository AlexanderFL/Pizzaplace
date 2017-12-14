#include "DeliveryUI.h"

DeliveryUI::DeliveryUI() {}

void DeliveryUI::deliveryMenu() {
	string input;
	while (true) {
		printMenu({ "Dislpay Orders", "Display Orders at location", "Back" }, "Delivery");
		getInput(input);
		if (input == "1") {
			clear();
			allOrdersMenu();
		}
		else if (input == "2") {
			clear();
			ordersMenu();
		}
		else if (input == "3") {
			clear();
			return;
		}
		else {
			clear();
			printMessage("Invalid input.");
		}
	}
}

void DeliveryUI::allOrdersMenu() {
	string input;
	while (true) {
		try {
			vector<Order> orders = service.getOrders();
			vector<string> names;
			for (size_t i = 0; i < orders.size(); ++i) {
				names.push_back("Pizza " + to_string(orders.at(i).getID()));
			}
			names.push_back("Back");
			printMenu(names, "Pizzas ready to be delivered");
			getInput(input);
			try {
				int index = service.convertStringToInt(input);
				if (index == names.size()) {
					clear();
					return;
				}
				try {
					clear();
					orderMenu(service.convertStringToInt(input) - 1, orders, -1);
				}
				catch (InvalidString) {
					clear();
					printMessage("Invalid input.");
				}
				catch (out_of_range) {
					clear();
					printMessage("Invalid index.");
				}
			}
			catch (InvalidString) {
				clear();
				printMessage("Invalid input.");
			}
		}
		catch (EmptyVector) {
			clear();
			printMessage("No orders available.");
			return;
		}
		catch (FailedOpenFile) {
			clear();
			printMessage("Failed to open file.");
			return;
		}
	}
}

void DeliveryUI::orderMenu(int index, vector<Order>& orders , int loc) {
	string input;
	while (true) {
		showOrderInfo(orders.at(index));
		cout << endl;
		if (!orders.at(index).isPaidFor()) {
			printMenu({ "Paid", "Go Back" }, "Set order as:");
			getInput(input);
			if (input == "1") {
				try {
					service.setOrderPaid(orders.at(index).getID());
					if (loc == -1) {
						orders = service.getOrders();
					}
					else {
						orders = service.getOrders(service.getItem<Location>(loc));
					}
					clear();
					printMessage("Order paid.");
				}
				catch (out_of_range) {
					clear();
					printMessage("Invalid input.");
				}
			}
			else if (input == "2") {
				clear();
				break;
			}
			else {
				clear();
				printMessage("Invalid input.");
			}
		}
		else {
			printMenu({ "Delivered", "Go Back" }, "Set order as:");
			getInput(input);
			if (input == "1") {
				try {
					service.setOrderDelivered(orders.at(index).getID());
					if (loc == -1) {
						orders = service.getOrders();
					}
					else {
						orders = service.getOrders(service.getItem<Location>(loc));
					}
					clear();
					printMessage("Order delivered.");
					break;
				}
				catch (out_of_range) {
					printMessage("Invalid index.");
				}
			}
			else if (input == "2") {
				clear();
				break;
			}
			else {
				clear();
				printMessage("Invalid input.");
			}
		}
	}
}

void DeliveryUI::ordersMenu() {
	string input;
	while (true) {
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
				int inputint = service.convertStringToInt(input);
				if (inputint == names.size()) {
					clear();
					return;
				}
				clear();
				int index = service.convertStringToInt(input) - 1;
				while (true) {
					names.clear();
					vector<Order> orders = service.getOrders(locations.at(index));
					for (size_t i = 0; i < orders.size(); ++i) {
						//cout << i + 1 << ": " << showPizzaInfoShort(pizzas.at(i)) << endl
						names.push_back("Pizza " + to_string(orders.at(i).getID()));
					}
					names.push_back("Back");

					//ADD NAME OF PLACE HERE
					printMenu(names, "Delivery from " + locations.at(index).getAddress());

					getInput(input);
					try {
						clear();
						orderMenu(service.convertStringToInt(input) - 1, orders, index);
					}
					catch (InvalidString) {
						clear();
						printMessage("Invalid input.");
					}
					catch (out_of_range) {
						clear();
						printMessage("Invalid index.");
					}
				}
			}
			catch (InvalidString) {
				clear();
				printMessage("Invalid input.");
			}
			catch (out_of_range) {
				clear();
				printMessage("Invalid index.");
			}
			catch (EmptyVector) {
				clear();
				printMessage("No orders available for this location");
			}
			catch (FailedOpenFile) {
				clear();
				printMessage("Failed to open file.");
			}
		}
		catch (EmptyVector) {
			clear();
			printMessage("No locations available.");
			return;
		}
		catch (FailedOpenFile) {
			clear();
			printMessage("Failed to open file.");
			return;
		}
	}
}
