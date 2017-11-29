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
            skráir mismunandi gerðir af pizzum (stærð og botn)
            skráir áleggstegunir
            ská ákveðnar samsetningar undir nafni (matseðill)
            ská aðrar vörur, td gos og brauðstangir
            sk´ra verð
            skrá afhendingarstaði
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
