#include <fstream>
#include "Pizza.h"

/*
*************************************************
				PUBLIC FUNCTIONS
*************************************************
*/

Pizza::Pizza()
{
    this->size = PizzaSize("Medium", 1);
    this->crust = PizzaCrust("Classic", 1000);
    this->phase = PREPERATION;
}

Pizza::Pizza(string name, vector<Topping> toppings)
{
    this->toppings = toppings;
    this->size = PizzaSize();
    this->crust = PizzaCrust();
    this->phase = PREPERATION;
}

vector<Topping>
Pizza::getToppings() const
{
    return this->toppings;
}

PizzaCrust
Pizza::getCrust() const
{
    return this->crust;
}

PizzaSize
Pizza::getPizzaSize() const
{
    return this->size;
}

status
Pizza::getPhase() const
{
    return this->phase;
}

size_t
Pizza::getID() const
{
    return this->id;
}

void
Pizza::addToppings(Topping topping)
{
    this->toppings.push_back(topping);
}

void
Pizza::setToppings(vector<Topping> toppings)
{
    this->toppings = toppings;
}

void
Pizza::setCrust(PizzaCrust &crust)
{
    this->crust = crust;
}

void
Pizza::setPizzaSize(const PizzaSize &size)
{
    this->size = size;
}

void
Pizza::setPhase(const status &phase)
{
    this->phase = phase;
}

void
Pizza::setID(const size_t &id)
{
    this->id = id;
}


/*
*************************************************
*****			PRIVATE FUNCTIONS			*****
*************************************************
*/


/*
*************************************************
				FRIEND FUNCTIONS
*************************************************
*/
ostream &
operator<<(ostream &out, const Pizza &pizza)
{
    if (&out != &cout)
    {
        size_t size = pizza.toppings.size();
        out.write((char *) (&size), sizeof(size_t));
        for (size_t i = 0; i < size; ++i)
        {
            out << pizza.toppings.at(i);
        }
        out << pizza.crust;
        out << pizza.size;
        out.write((char *) (&pizza.phase), sizeof(status));
        out.write((char *) (&pizza.id), sizeof(size_t));
    }
    else
    {
        for (int i = 0; i < pizza.toppings.size(); ++i)
        {
            out << pizza.toppings.at(i) << " ";
        }
    }
    return out;
}

istream &
operator>>(istream &in, Pizza &pizza)
{
    // TODO: Make this a function call to UI layer
    if (&in != &cin)
    {
        size_t size;
        in.read((char *) (&size), sizeof(size_t));
        pizza.toppings.clear();
        Topping topping;
        for (size_t i = 0; i < size; ++i)
        {
            in >> topping;
            pizza.toppings.push_back(topping);
        }
        in >> pizza.crust;
        in >> pizza.size;
        in.read((char *) (&pizza.phase), sizeof(status));
        in.read((char *) (&pizza.id), sizeof(size_t));
    }
    /*else {
        int size;
        do {
            cout << "Select pizza size:" << endl;
            cout << " 1: Small\t\t950kr.-" << endl;
            cout << " 2: Medium\t\t1150kr.-" << endl;
            cout << " 3: Large\t\t1450kr.-" << endl;
            cout << " Insert number: ";
            in >> size;
        } while (size < 1 || 3 < size);
        pizza.size = size;

        cout << "Select toppings: " << endl;

        for (int i = 0; i < pizza.nrToppings(); i++)
        {

        }
    }*/

    return in;
}

/*
	Compares whether the two pizzas have the same toppings
*/
bool
operator==(const Pizza &left, const Pizza &right)
{
    //if (left.size == right.size) {
    Pizza pizza = left * right;
    if (pizza.toppings.size() == left.toppings.size() && pizza.toppings.size() == right.toppings.size())
    {
        return true;
    }
    //}
    return false;
}

/*
	Compares whether the two pizzas do not have the same toppings
*/
bool
operator!=(const Pizza &left, const Pizza &right)
{
    return !(left == right);
}

/*
	Returns a pizza with the intersection for the toppings of two Pizzas
*/
Pizza
operator*(const Pizza &left, const Pizza &right)
{
    Pizza pizza;
    for (int i = 0; i < left.toppings.size(); ++i)
    {
        for (int j = 0; j < right.toppings.size(); ++j)
        {
            if (left.toppings.at(i) == right.toppings.at(j))
            {
                pizza.toppings.push_back(left.toppings.at(i));
                break;
            }
        }
    }
    return pizza;
}

/*
	Returns a pizza with the compenation for the toppings of two Pizzas
*/
Pizza
operator+(const Pizza &left, const Pizza &right)
{
    Pizza pizza = left;
    for (int i = 0; i < right.toppings.size(); ++i)
    {
        pizza.toppings.push_back(right.toppings.at(i));
    }
    return pizza;
}

/*
Returns a pizza with the compenation for the toppings of two Pizzas
*/
Pizza
operator-(const Pizza &left, const Pizza &right)
{
    Pizza pizza = left;
    Pizza temp = right;
    bool found = false;
    while (!temp.toppings.empty())
    {
        for (size_t i = 0; i < pizza.toppings.size(); ++i)
        {
            if (pizza.toppings.at(i) == temp.toppings.at(0))
            {
                pizza.toppings.erase(pizza.toppings.begin() + i);
                temp.toppings.erase(temp.toppings.begin());
                found = true;
                break;
            }
        }
        if (!found)
        {
            temp.toppings.erase(temp.toppings.begin());
        }
        found = false;
    }
    return pizza;
}