#include "MainUI.h"
#include "DeliveryUI.h"
#include "ManagerUI.h"
#include "SalesmanUI.h"
#include "KitchenUI.h"

/*MainUI::MainUI()
{
    //ctor
}*/

void MainUI::startUI()
{
    string input;
    while(true)
    {
        cout << "\nPlease Pick one of the following jobs:\n"
             << "\t-----------------------------\n"
             << "\t| Manager: M  | Salesman: S |\n"
             << "\t-----------------------------\n"
             << "\t| Kitchen: K  | Delivery: D |\n"
             << "\t-----------------------------\n"
			 << "Press 'q' to Quit\n"
             << "Job: ";

        cin >> input;

        transform(input.begin(), input.end(), input.begin(), ::tolower);

		if(input == "manager" ||input == "m")
        {
			ManagerUI managerUI;
			managerUI.managerMenu();
        }
        else if(input == "salesman" || input == "s")
        {
			SalesmanUI salesmanUI;
			salesmanUI.salesmanMenu();
        }
        else if(input == "kitchen" || input == "k")
        {
			KitchenUI kitchenUI;
			kitchenUI.kitchenMenu();
        }
        else if(input == "delivery" || input == "d")
        {
			DeliveryUI deliveryUI;
			deliveryUI.deliveryMenu();
        }
		else if (input == "quit" || input  == "q") {
			break;
		}
        else{
            cout << "Not a valid option." << endl;
        }
    }
}
