#include "Topping.h"

Topping::Topping(){}

void Topping::NewTopping(string name, double price, int level)
{
    if(level == 1)
    {
        //@todo append topping to file
    }
}

Topping Topping::instanciate()
{
	Topping t;
	return t;
}

ostream& operator<< (ostream& out, const Topping topping)
{
    out << topping.name << " " << topping.price;

    return out;
}
