#include "Location.h"
#include <fstream>

const string Location::filename = "locations.dat";

Location::Location() {}

Location::Location(string address)
	:address(address)
{
}

string Location::getAddress() const {
	return this->address;
}

size_t Location::getID() const {
	return this->id;
}

void Location::setAddress(const string& address) {
	this->address = address;
}

void Location::setID(const size_t& id) {
	this->id = id;
}

ostream& operator << (ostream& out, const Location& loc) {
	if (&out != &cout) {
		size_t len = loc.address.length() + 1;
		out.write((char*)(&len), sizeof(size_t));
		out.write(loc.address.c_str(), len);
		out.write((char*)(&loc.id), sizeof(size_t));
	}
	return out;
}

istream& operator >> (istream& in, Location& loc) {
	if (&in != &cin) {
		size_t len;
		in.read((char*)(&len), sizeof(size_t));
		char* str = new char[len];
		in.read(str, len);
		loc.address = str;
		delete[] str;
		in.read((char*)(&loc.id), sizeof(size_t));
	}
	else {
		in >> loc.address;
	}
	return in;
}

bool operator == (const Location& left, const Location& right) {
	if (left.address == right.address) {
		return true;
	}
	return false;
}