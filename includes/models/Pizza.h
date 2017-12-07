#pragma once
#include <iostream>
#include <vector>
#include "Topping.h"
#include "PizzaCrust.h"
#include "PizzaSize.h"
using namespace std;

class Pizza
{
private:
	// Change to vector
	vector<Topping> toppings;
	PizzaCrust crust;
	PizzaSize size;
	double cost;
	void calculateCost();
public:
	Pizza();
	Pizza(vector<Topping> toppings, PizzaCrust crust, PizzaSize size);
	void addTopping(const Topping& top);
	int nrToppings() const;
	double getCost();
	friend ostream& operator<< (ostream& out, const Pizza& pizza);
	friend istream& operator>> (istream& in, Pizza& pizza);
	friend bool operator == (const Pizza& left, const Pizza& right);
	friend bool operator != (const Pizza& left, const Pizza& right);
	friend Pizza operator * (const Pizza& left, const Pizza& right);
	friend Pizza operator + (const Pizza& left, const Pizza& right);

	int getToppingCount() const;
	Topping getToppingIndex(int index) const;
	vector<Topping> getToppings() const;
	PizzaCrust getCrust() const;
	PizzaSize getPizzaSize() const;
	void setToppings(const vector<Topping>& toppings);
	void setCrust(const PizzaCrust& crust);
	void setPizzaSize(const PizzaSize& size);
};
