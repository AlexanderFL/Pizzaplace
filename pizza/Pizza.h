#pragma once
#include <iostream>
#include <vector>
#include "Topping.h"
using namespace std;

class Pizza
{
private:
	// Change to vector
	vector<Topping> toppings;
	int size;
	double cost;
	void calculateCost();
public:
	Pizza();
	//~Pizza();
	void write(ofstream& fout) const;
	void read(ifstream& fin);
	double getCost();
	friend ostream& operator<< (ostream& out, const Pizza& pizza);
	friend istream& operator>> (istream& in, Pizza& pizza);
protected:

private:
};
