#include <fstream>
#include "Topping.h"

Topping::Topping(){}

void Topping::NewTopping(string name, double price)
{
	//@todo append topping to file
}

Topping* Topping::getAllToppings()
{
	Topping* t = new Topping[9];
	return t;
}

void Topping::write(ofstream& fout) const {
	int len = this->name.length();
	fout.write((char*)(&len), sizeof(int));
	for (int i = 0; i < len; ++i) {
		fout.write((char*)(&this->name[i]), sizeof(char));
	}
	fout.write((char*)(&this->price), sizeof(double));
}

void Topping::read(ifstream& fin) {
	int len;
	this->name = "";
	char n;
	fin.read((char*)(&len), sizeof(int));
	for (int i = 0; i < len; ++i) {
		fin.read(&n, sizeof(char));
		this->name += n;
	}
	fin.read((char*)(&this->price), sizeof(double));
}

double Topping::getPrice() {
	return this->price;
}

ostream& operator<< (ostream& out, const Topping topping)
{
    out << topping.name << " " << topping.price;

    return out;
}
