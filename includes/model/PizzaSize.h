#pragma once

#include <iostream>
#include <string>

using namespace std;

class PizzaSize
{
private:
	string name;
	double pricemod;
public:
	PizzaSize();
	PizzaSize(string name, double pricemod);
	string getName() const;
	double getPriceMod() const;
	void setName(const string& name);
	void setPriceMod(const double& pricemod);
	friend ostream& operator << (ostream& out, const PizzaSize& size);
	friend istream& operator >> (istream& in, PizzaSize& size);
	friend bool operator == (const PizzaSize& left, const PizzaSize& right);
};

