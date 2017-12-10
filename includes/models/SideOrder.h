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
	size_t id;
public:
	// Constructors
	SideOrder();
	SideOrder(string name, int price);

	// Get functions
	string getName() const;
	int getPrice() const;
	size_t getID() const;

	// Set functions
	void setName(const string& name);
	void setPrice(const int& price);
	void setID(const size_t& id);

	// Operator overloads
	friend ostream& operator<< (ostream& out, const SideOrder& side);
	friend istream& operator>> (istream& in, SideOrder& side);
	friend bool operator == (const SideOrder& left, const SideOrder& right);
};

