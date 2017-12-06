#include "PizzaCrust.h"
#include <fstream>

const string PizzaCrust::filename = "pizzacrusts.dat";

PizzaCrust::PizzaCrust() {
	this->price = 0;
}

PizzaCrust::PizzaCrust(string name, double price) {
	this->name = name;
	this->price = price;
}

string PizzaCrust::getName() const {
	return this->name;
}

double PizzaCrust::getPrice() const {
	return this->price;
}

void PizzaCrust::setName(const string& name) {
	this->name = name;
}

void PizzaCrust::setPrice(const double& price) {
	this->price = price;
}

ostream& operator << (ostream& out, const PizzaCrust& crust) {
	if (&out != &cout) {
		int len = crust.name.length() + 1;
		out.write((char*)(&len), sizeof(int));
		out.write(crust.name.c_str(), len);
		out.write((char*)(&crust.price), sizeof(double));
	}
	return out;
}

istream& operator >> (istream& in, PizzaCrust& crust) {
	if (&in != &cin) {
		int len;
		in.read((char*)(&len), sizeof(int));
		char* str = new char[len];
		in.read(str, len);
		crust.name = str;
		delete[] str;
		in.read((char*)(&crust.price), sizeof(double));
	}
	return in;
}