#include "LoginUI.h"
#include "ManagerUI.h"
#include "KitchenUI.h"
#include "SalesmanUI.h"
#include "DeliveryUI.h"
#include <iostream>

using namespace std;

void LoginUI::startUI() {
	char input;
	while (true) {
		cout << menu.printMenu({ "Login", "Exit" }) << endl;
		cout << "Input: ";
		cin >> input;
		switch (input)
		{
		case '1': {
			system("CLS");
			string username, password;
			cout << "Username: ";
			cin >> username;
			cout << "Password: ";
			cin >> password;
			try {
				profession job = service.login(username, password);
				switch (job) {
				case ADMIN: {
					//ADMIN MENU
					break;
				}
				case MANAGER: {
					ManagerUI managerUI;
					managerUI.managerMenu();
					break;
				}
				case SALESMAN: {
					SalesmanUI salesmanUI;
					salesmanUI.salesmanMenu();
					break;
				}
				case KITCHEN: {
					KitchenUI kitchenUI;
					kitchenUI.kitchenMenu();
					break;
				}
				case DELIVERY: {
					DeliveryUI deliveryUI;
					deliveryUI.deliveryMenu();
					break;
				}
				}
			}
			catch (InvalidLogin) {
				cout << "Username or Password was not correct!" << endl;
			}
			break;
		}
		case '2':
			exit(0);
			break;
		default:
			cout << "Invalid input!";
			break;
		}
	}
}