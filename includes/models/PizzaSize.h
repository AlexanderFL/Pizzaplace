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
	size_t id;
public:
	// Constructors
	PizzaSize();
	PizzaSize(string name, double pricemod);

	// Get functions
	string getName() const;
	double getPriceMod() const;
	size_t getID() const;

	// Set funcitons
	void setName(const string& name);
	void setPriceMod(const double& pricemod);
	void setID(const size_t& id);

	// Operator overloads
	friend ostream& operator << (ostream& out, const PizzaSize& size);
	friend istream& operator >> (istream& in, PizzaSize& size);
	friend bool operator == (const PizzaSize& left, const PizzaSize& right);
};

