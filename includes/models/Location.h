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
	/*		Constructors		*/
	Location();
	explicit Location(string address);

	/*		Get functions		*/
	// Gets the address of the Location
	string getAddress() const;
	// Just for a template, does the same as getAddress
	string getName() const;

	/*		Set functions		*/
	// Sets the address
	void setAddress(const string& address);

	/*		Operator overloads		*/
	friend ostream& operator << (ostream& out, const Location& loc);
	friend istream& operator >> (istream& in, Location& loc);
	friend bool operator == (const Location& left, const Location& right);
};

