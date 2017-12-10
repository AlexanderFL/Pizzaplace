#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PizzaCrust
{
public:
	static const string filename;
private:
	string name;
	int price;
public:
	// Constructors
	PizzaCrust();
	PizzaCrust(string name, int price);

	// Get functions
	string getName() const;
	int getPrice() const;

	// Set functions
	void setName(const string& name);
	void setPrice(const int& price);

	// Operator overloads
	friend ostream& operator << (ostream& out, const PizzaCrust& crust);
	friend istream& operator >> (istream& in, PizzaCrust& crust);
};
