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
	size_t id;
public:
	// Constructors
	Location();
	Location(string address);

	// Get functions
	string getAddress() const;
	size_t getID() const;

	// Set functions
	void setAddress(const string& address);
	void setID(const size_t& id);

	// Operator overloads
	friend ostream& operator << (ostream& out, const Location& loc);
	friend istream& operator >> (istream& in, Location& loc);
	friend bool operator == (const Location& left, const Location& right);
};

