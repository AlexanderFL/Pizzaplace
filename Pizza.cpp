#include "Pizza.h"

Pizza::Pizza()
{
	this->toppings = nullptr;
	this->nrOfToppings = 0;
}

Pizza::Pizza(int numberOfToppings)
{
	this->toppings = nullptr;
	this->nrOfToppings = numberOfToppings;
}

ostream& operator<< (ostream& out, const Pizza& pizza)
{
	out << pizza.toppings;

	return out;
}

istream& operator>> (istream& in, Pizza& pizza)
{
	cout << "Select pizza size:" << endl;
	cout << " 1: Small\t\t950kr.-" << endl;
	cout << " 2: Medium\t\t1150kr.-" << endl;
	cout << " 3: Large\t\t1450kr.-" << endl;
	cout << " Insert number: ";
	in >> pizza.size;

	cout << "Select toppings: " << endl;

	// TODO: change i < x, to corrisponding topping number
	for (int i = 0; i < 10; i++)
	{

	}
	return in;
}