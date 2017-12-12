#include "MainUI.h"
#include "DeliveryUI.h"
#include "ManagerUI.h"
#include "SalesmanUI.h"
#include "KitchenUI.h"
#include "CommonUI.h"
#include <stdlib.h>

void MainUI::startUI()
{
	char input;
	while (true)
	{
		system("CLS");
		cout << "\nPlease Pick one of the following jobs:\n"
			<< printMenu({ "Manager", "Salesman", "Kitchen", "Delivery" })
			<< "\nPress 'q' to quit.\nJob: ";

		cin >> input;

		switch (input)
		{
		case '1':
		{
			ManagerUI managerUI;
			managerUI.managerMenu();
			break;
		}
		case '2':
		{
			SalesmanUI salesmanUI;
			salesmanUI.salesmanMenu();
			break;
		}
		case '3':
		{
			KitchenUI kitchenUI;
			kitchenUI.kitchenMenu();
			break;
		}
		case '4':
		{
			DeliveryUI deliveryUI;
			deliveryUI.deliveryMenu();
			break;
		}
		case 'q':
		case 'Q':
			exit(1);
		default:
			cout << "Not a valid option." << endl;
		}
	}
}