#include "Topping.h"

Topping::Topping(string name, double price)
{
	this->name = name;
	this->price = price;
}

Topping::Topping(){}

vector<Topping> Topping::getAllToppings()
{
	vector<Topping> toppings;
	return toppings;
}

void Topping::write(ofstream& fout) const {
	//int len = this->name.length() + 1;
	int len = this->name.length();
	fout.write((char*)(&len), sizeof(int));
	char n;
	for (int i = 0; i < len; ++i) {
		n = this->name[i];
		fout.write(&n, sizeof(char));
	}
	//fout.write(this->name.c_str(), len);
	fout.write((char*)(&this->price), sizeof(double));
}

void Topping::read(ifstream& fin) {
	int len;
	this->name = "";
	fin.read((char*)(&len), sizeof(int));
	//char* str = new char[len];
	//fin.read(str, len);
	char n;
	for (int i = 0; i < len; ++i) {
		fin.read(&n, sizeof(char));
		this->name += n;
	}
	//this->name = str;
	fin.read((char*)(&this->price), sizeof(double));
	//delete[] str;
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