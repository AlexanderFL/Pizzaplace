#include <fstream>
#include "SideOrder.h"


SideOrder::SideOrder() {
	this->name = "";
	this->price = 0;
}

SideOrder::SideOrder(string name, double price) {
	this->name = name;
	this->price = price;
}


SideOrder::~SideOrder() {
}

void SideOrder::write(ofstream& fout) const {
	int len = this->name.length() + 1;
	fout.write((char*)(&len), sizeof(int));
	fout.write(this->name.c_str(), len);
	fout.write((char*)(&this->price), sizeof(double));
}

void SideOrder::read(ifstream& fin) {
	int len;
	this->name = "";
	fin.read((char*)(&len), sizeof(int));
	char* str = new char[len];
	fin.read(str, len);
	this->name = str;
	fin.read((char*)(&this->price), sizeof(double));
	delete[] str;
}

string SideOrder::getName() const {
	return this->name;
}

double SideOrder::getPrice() const {
	return this->price;
}

ostream& operator<< (ostream& out, const SideOrder& side) {
	out << side.name << " " << side.price;
	return out;
}

bool operator == (const SideOrder& left, const SideOrder& right) {
	return left.name == right.name && left.price == right.price;
}