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
	// Change to vector
	vector<Topping> toppings;
	PizzaCrust crust;
	PizzaSize size;
	status phase;
public:
	Pizza();
	Pizza(vector<Topping> toppings, PizzaCrust crust, PizzaSize size);
	friend ostream& operator<< (ostream& out, const Pizza& pizza);
	friend istream& operator>> (istream& in, Pizza& pizza);
	friend bool operator == (const Pizza& left, const Pizza& right);
	friend bool operator != (const Pizza& left, const Pizza& right);
	friend Pizza operator * (const Pizza& left, const Pizza& right);
	friend Pizza operator + (const Pizza& left, const Pizza& right);

	vector<Topping> getToppings() const;
	PizzaCrust getCrust() const;
	PizzaSize getPizzaSize() const;
	status getPhase() const;
	void setToppings(const vector<Topping>& toppings);
	void setCrust(const PizzaCrust& crust);
	void setPizzaSize(const PizzaSize& size);
	void setPhase(const status& phase);
};
