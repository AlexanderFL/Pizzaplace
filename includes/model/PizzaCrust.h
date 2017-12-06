#pragma once

#include <iostream>
#include <string>

using namespace std;

class PizzaCrust
{
private:
	string name;
	double price;
public:
	PizzaCrust();
	PizzaCrust(string name, double price);
	string getName() const;
	double getPrice() const;
	void setName(const string& name);
	void setPrice(const double& price);
	friend ostream& operator << (ostream& out, const PizzaCrust& crust);
	friend istream& operator >> (istream& in, PizzaCrust& crust);
};

