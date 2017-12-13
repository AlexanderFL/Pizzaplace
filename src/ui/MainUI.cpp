#include "MainUI.h"
#include "DeliveryUI.h"
#include "ManagerUI.h"
#include "SalesmanUI.h"
#include "KitchenUI.h"
#include <stdlib.h>

void MainUI::startUI()
{
	char input;
	while (true)
	{
		printMenu({ "Manager", "Salesman", "Kitchen", "Delivery", "Exit" }, "Main Menu");
		printInput("Input");
		cin >> input;

		switch (input)
		{
		case '1':
		{
			system("CLS");
			ManagerUI managerUI;
			managerUI.managerMenu();
			break;
		}
		case '2':
		{
			system("CLS");
			SalesmanUI salesmanUI;
			salesmanUI.salesmanMenu();
			break;
		}
		case '3':
		{
			system("CLS");
			KitchenUI kitchenUI;
			kitchenUI.kitchenMenu();
			break;
		}
		case '4':
		{
			system("CLS");
			DeliveryUI deliveryUI;
			deliveryUI.deliveryMenu();
			break;
		}
		case 'q':
		case 'Q':
			exit(0);
		default:
			system("CLS");
			printMessage("Not a valid option.");
			cout << endl;
		}
	}
}