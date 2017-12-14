#pragma once

#include <string>
#include <iostream>

using namespace std;

class Location
{
public:
	static const string filename;
private:
	string address;
public:
	// Constructors
	Location();
	explicit Location(string address);

	// Get functions
	string getAddress() const;
	// Just for a template
	string getName() const;

	// Set functions
	void setAddress(const string& address);

	// Operator overloads
	friend ostream& operator << (ostream& out, const Location& loc);
	friend istream& operator >> (istream& in, Location& loc);
	friend bool operator == (const Location& left, const Location& right);
};

