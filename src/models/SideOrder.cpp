#include <fstream>
#include "SideOrder.h"

const string SideOrder::filename = "sideorders.dat";

SideOrder::SideOrder() {
	this->name = "";
	this->price = 0;
}

SideOrder::SideOrder(string name, int price) {
	this->name = name;
	this->price = price;
}
string SideOrder::getName() const {
	return this->name;
}

int SideOrder::getPrice() const {
	return this->price;
}

void SideOrder::setName(const string& name) {
	this->name = name;
}

void SideOrder::setPrice(const int& price) {
	this->price = price;
}

ostream& operator<< (ostream& out, const SideOrder& side) {
	if (&out != &cout) {
		size_t len = side.name.length() + 1;
		out.write((char*)(&len), sizeof(size_t));
		out.write(side.name.c_str(), len);
		out.write((char*)(&side.price), sizeof(int));
	}
	else {
		out << side.name << " " << side.price;
	}
	return out;
}

istream& operator>> (istream& in, SideOrder& side) {
	if (&in != &cin) {
		size_t len;
		in.read((char*)(&len), sizeof(size_t));
		char* str = new char[len];
		in.read(str, len);
		side.name = str;
		in.read((char*)(&side.price), sizeof(int));
		delete[] str;
	}
	else {
		cout << "\nName: ";
		in >> side.name;
		cout << "Price: ";
		in >> side.price;
	}
	return in;
}

bool operator == (const SideOrder& left, const SideOrder& right) {
	return left.name == right.name && left.price == right.price;
}