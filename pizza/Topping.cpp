#include "Topping.h"

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

ostream& operator<< (ostream& out, const Topping topping)
{
    out << topping.name << " " << topping.price;
    return out;
}

bool operator == (const Topping& left, const Topping& right) {
	if (left.name == right.name && left.price == right.price) {
		return true;
	}
	return false;
}