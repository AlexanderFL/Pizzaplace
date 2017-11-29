#include "MainUI.h"

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
            /*
            skr�ir mismunandi ger�ir af pizzum (st�r� og botn)
            skr�ir �leggstegunir
            sk� �kve�nar samsetningar undir nafni (matse�ill)
            sk� a�rar v�rur, td gos og brau�stangir
            sk�ra ver�
            skr� afhendingarsta�i
            */
           cout << "bib";
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
            cout << "ma";
        }
        else{
            cout << "Not a valid option." << endl;
        }
    }
}
