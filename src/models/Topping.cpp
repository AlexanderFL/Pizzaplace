#include "Topping.h"

const string Topping::filename = "toppings.dat";

Topping::Topping() {
	name = "";
	price = 0;
}

Topping::Topping(string name, int price)
{
	this->name = name;
	this->price = price;
}

string Topping::getName() const {
	return this->name;
}

int Topping::getPrice() const{
	return this->price;
}

void Topping::setName(const string& name) {
	this->name = name;
}

void Topping::setPrice(const int& price) {
	this->price = price;
}

istream& operator >> (istream& in, Topping& topping) {
	if (&in != &cin) {
		size_t len;
		in.read((char*)(&len), sizeof(size_t));
		char* str = new char[len];
		in.read(str, len);
		topping.name = str;
		in.read((char*)(&topping.price), sizeof(int));
		delete[] str;
	}
	else {
		cout << "\nName: ";
		in >> topping.name;
		cout << "Price: ";
		in >> topping.price;
	}
	return in;
}

ostream& operator<< (ostream& out, const Topping& topping)
{
	if (&out != &cout) {
		size_t len = topping.name.length() + 1;
		out.write((char*)(&len), sizeof(size_t));
		out.write(topping.name.c_str(), len);
		out.write((char*)(&topping.price), sizeof(int));
	}
	else {
		out << "Name: " << topping.name << " | Price: " << topping.price << " Kr.";
	}
    return out;
}

bool operator == (const Topping& left, const Topping& right) {
	return left.name == right.name && left.price == right.price;
}