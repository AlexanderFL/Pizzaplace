#include "DeliveryUI.h"
#include "Order.h"
#include "CommonUI.h"

DeliveryUI::DeliveryUI() {}

void DeliveryUI::deliveryMenu() {
	string input;
	while (true) {
		printMenu({ "Dislpay Orders", "Display Orders at location", "Go Back" }, "Delivery");
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
				//cout << i + 1 << ": " << showPizzaInfoShort(pizzas.at(i)) << endl
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
					int order = service.convertStringToInt(input) - 1;
					showOrderInfo(orders.at(order));
					cout << endl;
					if (orders.at(order).isPaidFor()) {
						printMenu({ "Paid", "Go Back" }, "Set order as:");
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
							clear();
							break;
						}
						else {
							printMessage("Invalid input.");
						}
					}
					else {
						printMenu({ "Delivered", "Go Back" }, "Set order as:");
						getInput(input);
						if (input == "1") {
							try {
								service.setOrderDelivered(orders.at(order).getID());
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
							printMessage("Invalid input.");
						}
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
			int inputint = service.convertStringToInt(input);
			if (inputint == names.size()) {
				return;
			}
			else {
				try {
					names.clear();
					int index = service.convertStringToInt(input) - 1;
					vector<Order> orders = service.getOrders(locations.at(index));
					for (size_t i = 0; i < orders.size(); ++i) {
						//cout << i + 1 << ": " << showPizzaInfoShort(pizzas.at(i)) << endl
						names.push_back("Pizza " + to_string(orders.at(i).getID()));
					}
					names.push_back("Back");

					//ADD NAME OF PLACE HERE
					printMenu(names, "Delivery from " + locations.at(index).getAddress());
					getInput(input);

					int order = service.convertStringToInt(input) - 1;
					try {
						clear();
						showOrderInfo(orders.at(order));
						cout << endl;
						printMenu({ "Paid", "Delivered", "Go Back" }, "Set order as:");
						getInput(input);
						if (input == "1") {
							try {
								service.setOrderPaid(orders.at(order).getID());
							}
							catch (out_of_range) {
								printMessage("Invalid index.");
							}
						}
						if (input == "2") {
							try {
								service.setOrderPaid(orders.at(order).getID());
								service.setOrderDelivered(orders.at(order).getID());
							}
							catch (out_of_range) {
								printMessage("Invalid index.");
							}
						}
						if (input == "3") {
							break;
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

void DeliveryUI::showPizzaInfoShort(const Pizza& pizza) const {
	cout << pizza.getToppings().size() << " toppings, ";
	cout << pizza.getPizzaSize().getName() << " ";
	cout << pizza.getCrust().getName() << " pizza.";
}

void DeliveryUI::showOrderInfo(const Order& order) const {
	//TODO: FIX
	cout << "\n\t\tPizza Place " << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "Order ID: " << order.getID() << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "Pizza:\t\t\t";
	if (order.getPizzas().size() == 0) {
		cout << "None";
	}
	else {
		for (size_t i = 0; i < order.getPizzas().size(); ++i) {
			showPizzaInfoShort(order.getPizzas().at(i));
		}
		
	}
	cout << endl << "Side Orders:\t\t";
	if (order.getSides().size() == 0) {
		cout <<"None";
	}
	else {
		for (size_t i = 0; i < order.getSides().size(); ++i) {
			cout << order.getSides().at(i).getName();
		}
	}
	cout << endl << "Comment:\t\t" + order.getComment() << endl;
	cout << "Location:\t\t" + order.getLocation().getAddress() << endl;
	cout << "Delivery Method:\t";
	if (order.getDeliveryMethod() == PICKUP) {
		cout << "Pickup" << endl;
	}
	else if (order.getDeliveryMethod() == SEND) {
		cout << "Send to " << order.getHomeAddress() << endl;
	}
	cout << "Paid:\t\t\t";
	if (order.isPaidFor()) {
		cout << "True";
	}
	else {
		cout << "False" << endl;
	}
	cout << endl;
}

void DeliveryUI::showOrderInfoShort(const Order& order) const {
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