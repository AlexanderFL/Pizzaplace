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
	void write(ofstream& fout) const;
	void read(ifstream& fin);
	void addTopping(const Topping& top);
	int nrToppings() const;
	double getCost();
	friend ostream& operator<< (ostream& out, const Pizza& pizza);
	friend istream& operator>> (istream& in, Pizza& pizza);
	friend bool operator == (const Pizza& left, const Pizza& right);
	friend Pizza operator * (const Pizza& left, const Pizza& right);
	friend Pizza operator + (const Pizza& left, const Pizza& right);
};
