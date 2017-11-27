#include "Files.h"

Files::Files()
{
    this->finishedOrders = "FinishedOrdersFile.txt";
    this->menu = "MenuFile.txt";
    this->orders = "OrdersFile.txt";
}

/*
    Creates a new order in the system
*/
bool Files::AddOrder(Pizza pizza, string phone, string address="")
{
    ofstream fout;
    fout.open(orders, ios::app);



    fout.close();
}
