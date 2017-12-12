#include "PizzaSize.h"
#include <fstream>

const string PizzaSize::filename = "pizzasizes.dat";

PizzaSize::PizzaSize() {
	this->pricemod = 0;
}

PizzaSize::PizzaSize(string name, double pricemod) {
	this->name = name;
	setPriceMod(pricemod);
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
	if (pricemod <= 35 && pricemod >= 1)
	{
		double setModPercentage = 0;
		setModPercentage = (pricemod / 100) + 1;
		this->pricemod = setModPercentage;
	}
	else {
		this->pricemod = 5; // Some number to work with
	}
}

ostream& operator << (ostream& out, const PizzaSize& size) {
	if (&out != &cout) {
		size_t len = size.name.length() + 1;
		out.write((char*)(&len), sizeof(size_t));
		out.write(size.name.c_str(), len);
		out.write((char*)(&size.pricemod), sizeof(double));
	}
	return out;
}

istream& operator >> (istream& in, PizzaSize& size) {
	if (&in != &cin) {
		size_t len;
		in.read((char*)(&len), sizeof(size_t));
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