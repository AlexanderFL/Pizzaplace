#include "Topping.h"

const string Topping::filename = "toppings.dat";

Topping::Topping() {
	name = "";
	price = 0;
}

Topping::Topping(string name, double price)
{
	this->name = name;
	this->price = price;
}

vector<Topping> Topping::getAllToppings()
{
	vector<Topping> toppings;
	return toppings;
}

void Topping::write(ofstream& fout) const {
	int len = name.length() + 1;
	fout.write((char*)(&len), sizeof(int));
	fout.write(name.c_str(), len);
	fout.write((char*)(&price), sizeof(double));
}

/*
	Returns itself
*/
Topping Topping::self()
{
	Topping t(name, price);
	return t;
}

void Topping::read(ifstream& fin) {
	int len;
	this->name = "";
	fin.read((char*)(&len), sizeof(int));
	char* str = new char[len];
	fin.read(str, len);
	this->name = str;
	fin.read((char*)(&this->price), sizeof(double));
	delete[] str;
}

double Topping::getPrice() {
	return this->price;
}

istream& operator >> (istream& in, Topping& topping) {
	if (&in != &cin) {
		int len;
		topping.name = "";
		in.read((char*)(&len), sizeof(int));
		char* str = new char[len];
		in.read(str, len);
		topping.name = str;
		in.read((char*)(&topping.price), sizeof(double));
		delete[] str;
	}
	else {
		in >> topping.name;
	}
	return in;
}

ostream& operator<< (ostream& out, const Topping& topping)
{
	if (&out != &cout) {
		int len = topping.name.length() + 1;
		out.write((char*)(&len), sizeof(int));
		out.write(topping.name.c_str(), len);
		out.write((char*)(&topping.price), sizeof(double));
	}
	else {
		out << topping.name;
	}
    return out;
}

bool operator == (const Topping& left, const Topping& right) {
	return left.name == right.name && left.price == right.price;
}