#pragma once

#include <iostream>
#include <string>

using namespace std;

class SideOrder {
public:
	static const string filename;
private:
	string name;
	int price;
public:
	// Constructors
	SideOrder();
	SideOrder(const string& name, int price);

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
	friend ostream& operator<< (ostream& out, const SideOrder& side);
	friend istream& operator>> (istream& in, SideOrder& side);
	friend bool operator == (const SideOrder& left, const SideOrder& right);
};

