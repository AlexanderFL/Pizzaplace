#include "PizzaSize.h"
#include <fstream>


PizzaSize::PizzaSize() {
	this->pricemod = 1;
}

PizzaSize::PizzaSize(string name, double pricemod) {
	this->name = name;
	this->pricemod = pricemod;
}

string PizzaSize::getName() const {
	return this->name;
}

double PizzaSize::getPriceMod() const {
	return this->pricemod;
}

void PizzaSize::setName(const string& name) {
	this->name = name;
}

void PizzaSize::setPriceMod(const double& pricemod) {
	this->pricemod = pricemod;
}

ostream& operator << (ostream& out, const PizzaSize& size) {
	if (&out != &cout) {
		int len = size.name.length() + 1;
		out.write((char*)(&len), sizeof(int));
		out.write(size.name.c_str(), len);
		out.write((char*)(&size.pricemod), sizeof(double));
	}
	return out;
}

istream& operator >> (istream& in, PizzaSize& size) {
	if (&in != &cin) {
		int len;
		in.read((char*)(&len), sizeof(int));
		char* str = new char[len];
		in.read(str, len);
		size.name = str;
		delete[] str;
		in.read((char*)(&size.pricemod), sizeof(double));
	}
	return in;
}

bool operator == (const PizzaSize& left, const PizzaSize& right) {
	return left.name == right.name && left.pricemod == right.pricemod;
}