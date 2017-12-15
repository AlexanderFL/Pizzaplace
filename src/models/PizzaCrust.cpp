#include "PizzaCrust.h"
#include <fstream>

const string PizzaCrust::filename = "pizzacrusts.dat";

PizzaCrust::PizzaCrust()
	: name(""), price(0)
{

}

PizzaCrust::PizzaCrust(const string name, int price)
	: name(name), price(price)
{

}

string PizzaCrust::getName() const
{
	return this->name;
}

int PizzaCrust::getPrice() const
{
	return this->price;
}

void PizzaCrust::setName(const string &name)
{
	this->name = name;
}

void PizzaCrust::setPrice(const int &price)
{
	this->price = price;
}

ostream &operator<<(ostream &out, const PizzaCrust &crust)
{
	if (&out != &cout)
	{
		size_t len = crust.name.length() + 1;
		out.write((char *)(&len), sizeof(size_t));
		out.write(crust.name.c_str(), len);
		out.write((char *)(&crust.price), sizeof(int));
	}
	return out;
}

istream &operator>>(istream &in, PizzaCrust &crust)
{
	if (&in != &cin)
	{
		size_t len;
		in.read((char *)(&len), sizeof(size_t));
		char *str = new char[len];
		in.read(str, len);
		crust.name = str;
		delete[] str;
		in.read((char *)(&crust.price), sizeof(int));
	}
	else
	{
		cout << "\nName: ";
		in >> crust.name;
		cout << "Price: ";
		in >> crust.price;
	}
	return in;
}