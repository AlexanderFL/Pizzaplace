#pragma once

#include <iostream>
#include <string>

using namespace std;

class PizzaSize
{
public:
	static const string filename;
private:
	string name;
	double pricemod;
public:
	// Constructors
	PizzaSize();
	PizzaSize(const string& name, double pricemod);

	// Get functions
	string getName() const;
	double getPriceMod() const;

	// Set funcitons
	void setName(const string& name);
	void setPriceMod(const double& pricemod);

	// Operator overloads
	friend ostream& operator << (ostream& out, const PizzaSize& size);
	friend istream& operator >> (istream& in, PizzaSize& size);
	friend bool operator == (const PizzaSize& left, const PizzaSize& right);
};

