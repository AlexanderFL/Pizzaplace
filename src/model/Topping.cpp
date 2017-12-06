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

double Topping::getPrice() const{
	return this->price;
}
string Topping::getName() const{
	return this->name;
}

istream& operator >> (istream& in, Topping& topping) {
	if (&in != &cin) {
		int len;
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