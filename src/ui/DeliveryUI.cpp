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
	/*string homeAddress;
	Order order;
	//TODO: Kalla í fallið numberOfOrders þegar það er tilbúið og setja útkomuna í int numberOfOrders 
	char input;
	int numberOfInput = 0;
	while (true) {
		cout << "Where would you like it delivered? ";
		cin.ignore();
		getline(cin, homeAddress);
		cout << "Your home address is " << homeAddress << ". Is this correct? (y/n): ";
		cin >> input;
		if (tolower(input) == 'y') {
			break;
		}
		//To be able to use getline again without error
		cin.clear();
		cin.sync();
	}
	cout << "This home address has " << numberOfInput << " order";

	if (numberOfInput > 1) {
		cout << "s.\nYour orders are: ";
		//Add orders here
	}
	else if (numberOfInput == 1) {
		cout << "Your order is:";
	}
	else {
		cout << "s.";
	}
	cout << "\nWould you like to add an Order?(y/n): ";
	cin >> input;
	if (tolower(input) == 'y') {
		//call the function to add an order
	}
	//TODO: Call a function to delete an Order, if orders  >= 1.
	*/
	char input;
	Menu menu;
	while (true) {
		cout << menu.printMenu({ "Dislpay Orders", "Display Orders at location", "Go Back" }) << endl;
		cin >> input;
		switch (input)
		{
		case '1': {
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
							service.setOrderPaid(order);
						}
						catch (out_of_range) {
							cout << "Invalid index" << endl;
						}
						break;
					}
					case '2': {
						try {
							service.setOrderDelivered(order);
						}
						catch (out_of_range) {
							cout << "Invalid index" << endl;
						}
						break;
					}
					case '3': {
						return;
					}
					default:
						cout << "Invalid input" << endl;
						break;
					}
				}
				catch (out_of_range) {
					cout << "Invalid index" << endl;
				}
			}
			catch (EmptyVector) {
				cout << "No orders av" << endl;
			}
			catch (FailedOpenFile) {
				cout << "Failed opne file 1" << endl;
			}
			break;
		}
		case '2': {
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
						cout << i + 1 << ": " <<  orders.at(i).getStatus() << endl;
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
								service.setOrderPaid(order);
							}
							catch (out_of_range) {
								cout << "Invalid index" << endl;
							}
							break;
						}
						case '2': {
							try {
								service.setOrderDelivered(order);
							}
							catch (out_of_range) {
								cout << "Invalid index" << endl;
							}
							break;
						}
						case '3': {
							return;
						}
						default:
							cout << "Invalid input" << endl;
							break;
						}
					}
					catch (out_of_range) {
						cout << "Invalid index" << endl;
					}
				}
				catch (out_of_range) {
					cout << "Invalid index" << endl;
				}
				catch (EmptyVector) {
					cout << "No orders av" << endl;
				}
				catch (FailedOpenFile) {
					cout << "Failed open file 2" << endl;
				}
			}
			catch (EmptyVector) {
				cout << "No locations av" << endl;
			}
			catch (FailedOpenFile) {
				cout << "Failed opne file 1" << endl;
			}
			break;
		}
		case '3': {
			return;
		}
		default:
			cout << "Invalid input" << endl;
			break;
		}
	}
}
