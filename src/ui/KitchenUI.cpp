#include "KitchenUI.h"

KitchenUI::KitchenUI() {}

void KitchenUI::showMainMenu() {
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
				try {
					getInput(input);
					int index = service.convertStringToInt(input);
					int place = index - 1;
					if (index == names.size()) {
						clear();
						return;
					}
					vector<Pizza> pizzas = service.getPizzas(locations.at(place));
					clear();
					while (true) {
						names.clear();
						for (size_t i = 0; i < pizzas.size(); ++i) {
							//cout << i + 1 << ": " << showPizzaInfoShort(pizzas.at(i)) << endl
							names.push_back("Pizza " + to_string(pizzas.at(i).getID()));
						}
						names.push_back("Back");
						printMenu(names, "Incomplete Pizzas");
						getInput(input);
							try {
								index = service.convertStringToInt(input);
								if (index == names.size()) {
									clear();
									break;
								}
								clear();
								while (true) {
									printMessage(showPizzaInfo(pizzas.at(index - 1)));
									if (pizzas.at(index - 1).getPhase() == PREPERATION) {
										printMenu({ "Set as Baking", "Back" }, "Select option");
										getInput(input);
										if (input == "1") {
											clear();
											service.setOrderAsBaking(pizzas.at(index - 1).getID());
											pizzas = service.getPizzas(locations.at(place));
											printMessage("Pizza set to baking.");
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
										printMenu({ "Set as Ready", "Back" }, "Pizza things menu");
										getInput(input);
										if (input == "1") {
											clear();
											service.setOrderAsReady(pizzas.at(index - 1).getID());
											pizzas = service.getPizzas(locations.at(place));
											printMessage("Pizza set to ready.");
											break;
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
							catch (out_of_range) {
								clear();
								printMessage("Invalid index.");
							}
					}
				}
				catch (NumberInString) {
					clear();
					printMessage("Invalid input.");
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
					printMessage("No pizzas available for this location.");
				}
				catch (FailedOpenFile) {
					clear();
					printMessage("Failed to open file.");
				}
		}
		catch (EmptyVector) {
			clear();
			printMessage("No locations available.");
			break;
		}
		catch (FailedOpenFile) {
			clear();
			printMessage("Failed to open file.");
			return;
		}
	}
}

void KitchenUI::kitchenMenu() {
	string input;
	while (true) {
		try {
 			vector<Location> locations = service.getItems<Location>();
			cout << "Choose the location of your workplace" << endl;
			for (size_t i = 0; i < locations.size(); ++i) {
				cout << i + 1 << ": " << locations.at(i).getAddress() << endl;
			}
			cout << "0: Go back" << endl;
			cout << "Input: ";
			cin >> ws;
			getline(cin, input);
			if (input == "0") {
				return;
			}
			else {
				try {
					int index = service.convertStringToInt(input) - 1;
					vector<Pizza> pizzas = service.getPizzas(locations.at(index));
					while (true) {
						for (size_t i = 0; i < pizzas.size(); ++i) {
							cout << i + 1 << ": " << showPizzaInfoShort(pizzas.at(i)) << endl;
						}
						cout << "0: Go back" << endl;
						cout << "Input: ";
						cin >> ws;
						getline(cin, input);
						if (input == "0") {
							return;
						}
						else {
							try {
								int pizzanr = service.convertStringToInt(input) - 1;
								while (true) {
									cout << showPizzaInfo(pizzas.at(pizzanr)) << endl;
									cout << "1: Set as Baking" << endl;
									cout << "2: Set as Ready" << endl;
									cout << "3: Go Back" << endl;
									cout << "Input: ";
									cin >> ws;
									getline(cin, input);
									if (input == "1") {
										service.setOrderAsBaking(pizzas.at(pizzanr).getID());
										pizzas = service.getPizzas(locations.at(index));
									}
									else if (input == "2") {
										service.setOrderAsReady(pizzas.at(pizzanr).getID());
										pizzas = service.getPizzas(locations.at(index));
									}
									else if (input == "3") {
										break;
									}
									else {
										cout << "Invalid input.";
									}
								}
							}
							catch (out_of_range) {
								cout << "Invalid index." << endl;
							}
						}
					}
				}
				catch (InvalidString) {
					cout << "Invalid input." << endl;
				}
				catch (out_of_range) {
					cout << "Invalid index." << endl;
				}
				catch (EmptyVector) {
					cout << "No pizzas available for this location." << endl;
				}
				catch (FailedOpenFile) {
					cout << "Failed to open file." << endl;
				}
			}
		}
		catch (EmptyVector) {
			cout << "No locations available." << endl;
			break;
		}
		catch (FailedOpenFile) {
			cout << "Failed to open file." << endl;
			break;
		}
	}
}

string KitchenUI::showPizzaInfo(const Pizza& pizza) const {
	string info = "A ";
	info += pizza.getPizzaSize().getName() + " pizza with ";
	if (pizza.getToppings().size() == 0) {
		info += "no toppings, ";
	}
	else {
		for (size_t i = 0; i < pizza.getToppings().size(); ++i) {
			info += pizza.getToppings().at(i).getName() + ", ";
		}
	}
	info += pizza.getCrust().getName() + " crust.";
	info += " It is currently";
	if (pizza.getPhase() == PREPERATION) {
		info += " in preperation.";
	}
	else if (pizza.getPhase() == BAKING) {
		info += " baking.";
	}
	return info;
}

string KitchenUI::showPizzaInfoShort(const Pizza& pizza) const {
	string info = "Pizza ";
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