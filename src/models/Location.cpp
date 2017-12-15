#include "Location.h"
#include <fstream>

const string Location::filename = "locations.dat";

/*
*************************************************
			PUBLIC FUNCTIONS
*************************************************
*/

Location::Location() {}

/*		Get functions		*/
Location::Location(const string address)
	: address(address) {}

string Location::getAddress() const
{
	return this->address;
}

string Location::getName() const
{
	return this->address;
}

/*		Set functions		*/
void Location::setAddress(const string &address)
{
	this->address = address;
}

/*		Operator overloads		*/
ostream &operator<<(ostream &out, const Location &loc)
{
	if (&out != &cout)
	{
		size_t len = loc.address.length() + 1;
		out.write((char *)(&len), sizeof(size_t));
		out.write(loc.address.c_str(), len);
	}
	return out;
}

istream &operator>>(istream &in, Location &loc)
{
	if (&in != &cin)
	{
		size_t len;
		in.read((char *)(&len), sizeof(size_t));
		char *str = new char[len];
		in.read(str, len);
		loc.address = str;
		delete[] str;
	}
	else
	{
		in >> loc.address;
	}
	return in;
}

bool operator==(const Location &left, const Location &right)
{
	if (left.address == right.address)
	{
		return true;
	}
	return false;
}