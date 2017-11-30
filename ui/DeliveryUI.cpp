#include "DeliveryUI.h"


DeliveryUI::DeliveryUI()
{
}


//Afhendingin

void DeliveryUI::menu()
{
	string homeAddress;
	int numberofOrders = 0;
	char input;
	while (true)
	{
		cout << "Where would you like it delivered? ";
		getline(cin, homeAddress);
		cout << "Your home address is " << homeAddress << ". Is this correct?(y/n): ";
		cin >> input;
		if (tolower(input) == 'y')
		{
			break;
		}
		//To be able to use getline again without error
		cin.clear();
		cin.sync();
	}
	if (numberofOrders > 1)
	{
		cout << homeAddress << " has " << numberofOrders << " orders." << endl;
		cout << "Your orders are: ";
		for (int i = 0; i < numberofOrders; i++)
		{
			cout << "hisfg";
		}
	}
	else if (numberofOrders == 1)
	{
		cout << homeAddress << " has 1 order." << endl;
		cout << "Your order is ";
	}
	else
	{
		cout << "This home address doesn't have any orders. \nWould you like to add an order?(y/n): ";
		cin >> input;
		if (tolower(input) == 'y')
		{
			//call the function to add an order
			cout << "hiahe";
		}
	}
}
