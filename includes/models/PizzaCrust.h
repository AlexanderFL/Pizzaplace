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
	//Gets the name
	string getName() const;
	//Gets the price
	int getPrice() const;

	// Set functions
	//Sets the name
	void setName(const string& name);
	//Sets the price
	void setPrice(const int& price);

	// Operator overloads
	friend ostream& operator << (ostream& out, const PizzaCrust& crust);
	friend istream& operator >> (istream& in, PizzaCrust& crust);
};
