#include "Topping.h"

Topping::Topping(){}

void Topping::NewTopping(string name, double price)
{
	//@todo append topping to file
}

Topping* Topping::getAllToppings()
{
	Topping* t = new Topping[9];
	return t;
}

ostream& operator<< (ostream& out, const Topping topping)
{
    out << topping.name << " " << topping.price;

    return out;
}
