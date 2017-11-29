#include "Order.h"

/*
	PUBLIC FUNCTIONS
*/

Order::Order() 
{ 
	totalCost = 0;
}

void Order::MakeOrder()
{
	Pizza tempPizza;
	cout << "New Order" << endl;
	cin >> tempPizza;
}

/*
	PRIVATE FUNCTIONS
*/


/*
FRIEND FUNCTIONS
*/

ostream& operator<<(ostream& out, const Order& order)
{
	out << order;

	return out;
}