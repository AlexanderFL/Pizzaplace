#include "Location.h"
#include <fstream>

const string Location::filename = "locations.dat";

Location::Location(string address)
	:address(address)
{
}

string Location::getAddress() const {
	return this->address;
}

void Location::setAddress(const string& address) {
	this->address = address;
}

ostream& operator << (ostream& out, const Location& loc) {
	if (&out != &cout) {
		int len = loc.address.length() + 1;
		out.write((char*)(&len), sizeof(int));
		out.write(loc.address.c_str(), len);
	}
	return out;
}

istream& operator >> (istream& in, Location& loc) {
	if (&in != &cin) {
		int len;
		in.read((char*)(&len), sizeof(int));
		char* str = new char[len];
		in.read(str, len);
		loc.address = str;
		delete[] str;
	}
	return in;
}