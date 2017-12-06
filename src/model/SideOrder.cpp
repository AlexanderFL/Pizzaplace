#include <fstream>
#include "SideOrder.h"

const string SideOrder::filename = "sideOrder.dat";

SideOrder::SideOrder() {
	this->name = "";
	this->price = 0;
}

SideOrder::SideOrder(string name, double price) {
	this->name = name;
	this->price = price;
}
string SideOrder::getName() const {
	return this->name;
}

double SideOrder::getPrice() const {
	return this->price;
}

ostream& operator<< (ostream& out, const SideOrder& side) {
	if (&out != &cout) {
		int len = side.name.length() + 1;
		out.write((char*)(&len), sizeof(int));
		out.write(side.name.c_str(), len);
		out.write((char*)(&side.price), sizeof(double));
	}
	else {
		out << side.name << " " << side.price;
	}
	return out;
}

istream& operator>> (istream& in, SideOrder& side) {
	if (&in != &cin) {
		int len;
		in.read((char*)(&len), sizeof(int));
		char* str = new char[len];
		in.read(str, len);
		side.name = str;
		in.read((char*)(&side.price), sizeof(double));
		delete[] str;
	}
	return in;
}

bool operator == (const SideOrder& left, const SideOrder& right) {
	return left.name == right.name && left.price == right.price;
}