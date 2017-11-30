#include "MainUI.h"
#include "DeliveryUI.h"
#include "ManagerUI.h"

MainUI::MainUI()
{
    //ctor
}

MainUI::~MainUI()
{
    //dtor
}

void MainUI::startUI()
{
    string input;
    while(true)
    {
        cout << "\nPlease Pick one of the following jobs:\n"
             << "\t-----------------------\n"
             << "\t| Manager  | Salesman |\n"
             << "\t-----------------------\n"
             << "\t| Kitchen  | Delivery |\n"
             << "\t-----------------------\n"
             << "Job: ";

        cin >> input;

        transform(input.begin(), input.end(), input.begin(), ::tolower);

        if(input == "manager")
        {
			ManagerUI managerUI;
			managerUI.managerMenu();
        }
        else if(input == "salesman")
        {
            cout << "gf";
            //Pizza newPizza;
            //newPizza.toppingsAmount();
        }
        else if(input == "kitchen")
        {
            cout << "dor";
        }
        else if(input == "delivery")
        {
			DeliveryUI deliveryUI;
			deliveryUI.deliveryMenu();
        }
		else if (input == "quit") {
			break;
		}
        else{
            cout << "Not a valid option." << endl;
        }
    }
}
