#include "Offer.h"
#include <fstream>

const string Offer::filename = "offers.dat";

Offer::Offer()
{
	name = "Unnamed";
	price = 0;
}

Offer::Offer(string name, Order order, int price)
	: name(name), order(order), price(price) {}

string Offer::getName() const
{
	return this->name;
}

Order Offer::getOrder() const
{
	return this->order;
}

int Offer::getPrice() const
{
	return this->price;
}

void Offer::setName(const string &name)
{
	this->name = name;
}

void Offer::setOrder(const Order &order)
{
	this->order = order;
}

void Offer::setPrice(const int &price)
{
	this->price = price;
}

ostream &operator<<(ostream &out, const Offer &offer)
{
	if (&out != &cout)
	{
		size_t len = offer.name.length() + 1;
		out.write((char *)(&len), sizeof(size_t));
		out.write(offer.name.c_str(), len);
		out << offer.order;
		out.write((char *)(&offer.price), sizeof(int));
	}
	else
	{
		cout << "Name: " << offer.name << endl;
		cout << "Price: " << offer.price << endl;
	}
	return out;
}

istream &operator>>(istream &in, Offer &offer)
{
	if (&in != &cin)
	{
		size_t len;
		in.read((char *)(&len), sizeof(size_t));
		char *str = new char[len];
		in.read(str, len);
		offer.name = str;
		delete[] str;
		in >> offer.order;
		in.read((char *)(&offer.price), sizeof(int));
	}
	else
	{
		cout << "\nName: ";
		in >> offer.name;
		cout << "Price: ";
		in >> offer.price;
	}
	return in;
}