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
	int postalCode;
	string city;
public:
	Location();
	Location(string address);

	void setAddress(const string& address);
	string getAddress() const;

	friend ostream& operator << (ostream& out, const Location& loc);
	friend istream& operator >> (istream& in, Location& loc);
};

