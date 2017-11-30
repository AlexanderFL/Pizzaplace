#pragma once
#include <iostream>
#include "Topping.h"
using namespace std;

class Pizza
{
private:
	Topping* toppings;
	int nrOfToppings;
	int size;
	int cost;

public:
	Pizza();
	Pizza(int numberOfToppings);
	void write(ofstream& fout) const;
	void read(ifstream& fin);
	friend ostream& operator<< (ostream& out, const Pizza& pizza);
	friend istream& operator>> (istream& in, Pizza& pizza);
protected:

private:
};
