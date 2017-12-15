#pragma once
#include <iostream>
#include <vector>
#include "Topping.h"
#include "PizzaCrust.h"
#include "PizzaSize.h"
using namespace std;

enum status { PREPERATION = 0, BAKING, READY, SENT };

class Pizza
{
private:
    vector<Topping> toppings;
    PizzaCrust crust;
    PizzaSize size;
    status phase;
    size_t id;
public:
    /*	Constructors	*/
    Pizza();
    Pizza(string name, vector<Topping> toppings);

    /*	Get Functions	*/
    //Gets all the toppings
    vector<Topping> getToppings() const;
    //Gets the pizza crust
    PizzaCrust getCrust() const;
    //Gets the pizza size
    PizzaSize getPizzaSize() const;
    //Gets the phase
    status getPhase() const;
    //Gets the ID
    size_t getID() const;

    //Adds a topping to the toppings
    void addToppings(Topping topping);

    /*	Set Functions	*/
    //Sets the toppings
    void setToppings(vector<Topping> toppings);
    //Sets the pizza crust
    void setCrust(PizzaCrust &crust);
    //Sets the pizza size
    void setPizzaSize(const PizzaSize &size);
    //Sets the phase
    void setPhase(const status &phase);
    //Sets the ID
    void setID(const size_t &id);

    /*	Operator Overloads	*/
    friend ostream &operator<<(ostream &out, const Pizza &pizza);
    friend istream &operator>>(istream &in, Pizza &pizza);
    friend bool operator==(const Pizza &left, const Pizza &right);
    friend bool operator!=(const Pizza &left, const Pizza &right);
    friend Pizza operator*(const Pizza &left, const Pizza &right);
    friend Pizza operator+(const Pizza &left, const Pizza &right);
    friend Pizza operator-(const Pizza &left, const Pizza &right);
};
