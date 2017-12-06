#include "Location.h"
#include <fstream>


Location::Location() {}

Location::Location(string name) {
	this->name = name;
}

string Location::getName() const {
	return this->name;
}

void Location::setName(const string& name) {
	this->name = name;
}

ostream& operator << (ostream& out, const Location& loc) {
	if (&out != &cout) {
		int len = loc.name.length() + 1;
		out.write((char*)(&len), sizeof(int));
		out.write(loc.name.c_str(), len);
	}
	return out;
}

istream& operator >> (istream& in, Location& loc) {
	if (&in != &cin) {
		int len;
		in.read((char*)(&len), sizeof(int));
		char* str = new char[len];
		in.read(str, len);
		loc.name = str;
		delete[] str;
	}
	return in;
}