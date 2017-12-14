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
	string name;
	int price;
public:
	// Constructors
	Pizza();
	Pizza(string name, vector<Topping> toppings, int price);

	// Get functions
	vector<Topping> getToppings() const;
	PizzaCrust getCrust() const;
	PizzaSize getPizzaSize() const;
	status getPhase() const;
	size_t getID() const;

	// Set Functions
	void addToppings(Topping topping);
	void setToppings(vector<Topping> toppings);
	void setCrust(const PizzaCrust& crust);
	void setPizzaSize(const PizzaSize& size);
	void setPhase(const status& phase);
	void setID(const size_t& id);

	// Operator overloads
	friend ostream& operator<< (ostream& out, const Pizza& pizza);
	friend istream& operator>> (istream& in, Pizza& pizza);
	friend bool operator == (const Pizza& left, const Pizza& right);
	friend bool operator != (const Pizza& left, const Pizza& right);
	friend Pizza operator * (const Pizza& left, const Pizza& right);
	friend Pizza operator + (const Pizza& left, const Pizza& right);
	friend Pizza operator - (const Pizza& left, const Pizza& right);
};
