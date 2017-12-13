#include "MainUI.h"
#include "DeliveryUI.h"
#include "ManagerUI.h"
#include "SalesmanUI.h"
#include "KitchenUI.h"

void MainUI::startUI()
{
	string input;
	while (true)
	{
		printMenu({ "Manager", "Salesman", "Kitchen", "Delivery", "Exit"}, "Main Menu");
		getInput(input);

		if (input == "1") {
			clear();
			ManagerUI managerUI;
			managerUI.managerMenu();
			//managerUI.showMainMenu();
		}
		else if (input == "2") {
			clear();
			SalesmanUI salesmanUI;
			salesmanUI.salesmanMenu();
		}
		else if (input == "3") {
			clear();
			KitchenUI kitchenUI;
			//kitchenUI.kitchenMenu();
			kitchenUI.showMainMenu();
		}
		else if (input == "4") {
			clear();
			DeliveryUI deliveryUI;
			deliveryUI.deliveryMenu();
		}
		else if (input == "5") {
			exit(0);
		} 
		else {
			clear();
			printMessage("Not a valid option.");
		}
	}
}