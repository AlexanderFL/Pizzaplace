#include "MainUI.h"
#include "DeliveryUI.h"
#include "ManagerUI.h"
#include "SalesmanUI.h"
#include "KitchenUI.h"

void
MainUI::startUI()
{
    cout << " _____ _                _____  _\n"
         << "|  __ (_)              |  __ \\| |\n"
         << "| |__)  |__________ _  | |__) | | __ _  ___ ___\n"
         << "|  ___/ |_  /_  / _` | |  ___/| |/ _` |/ __/ _ \\\n"
         << "| |   | |/ / / / (_| | | |    | | (_| | (_|  __/\n"
         << "|_|   |_/___/___\\__,_| |_|    |_|\\__,_|\___\___|" << endl;

    system("PAUSE");
    string input;
    clear();
    while (true)
    {
        printMenu({"Manager", "Salesman", "Kitchen", "Delivery", "Exit"}, "Main Menu");
        getInput(input);

        if (input == "1")
        {
            clear();
            ManagerUI managerUI;
            managerUI.showMainMenu();
        }
        else if (input == "2")
        {
            clear();
            SalesmanUI salesmanUI;
            salesmanUI.salesmanMenu();
        }
        else if (input == "3")
        {
            clear();
            KitchenUI kitchenUI;
            kitchenUI.showMainMenu();
        }
        else if (input == "4")
        {
            clear();
            DeliveryUI deliveryUI;
            deliveryUI.deliveryMenu();
        }
        else if (input == "5")
        {
            exit(0);
        }
        else
        {
            clear();
            printMessage("Invalid input.");
        }
    }
}