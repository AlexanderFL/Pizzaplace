#include "Offer.h"
#include <fstream>

const string Offer::filename = "offers.dat";

Offer::Offer() {
	price = 0;
	fixed = true;
}

Offer::Offer(string name, Order order, int price, bool fixed)
	:name(name), order(order), price(price), fixed(fixed)
{
}

string Offer::getName() const {
	return this->name;
}

Order Offer::getOrder() const {
	return this->order;
}

int Offer::getPrice() const {
	return this->price;
}

bool Offer::getFixed() const {
	return this->fixed;
}

void Offer::setName(const string& name) {
	this->name = name;
}

void Offer::setOrder(const Order& order) {
	this->order = order;
}

void Offer::setPrice(const int& price) {
	this->price = price;
}

void Offer::setFixed(const bool& fixed) {
	this->fixed = fixed;
}

ostream& operator << (ostream& out, const Offer& offer) {
	if (&out != &cout) {
		size_t len = offer.name.length() + 1;
		out.write((char*)(&len), sizeof(size_t));
		out.write(offer.name.c_str(), len);
		out << offer.order;
		out.write((char*)(&offer.price), sizeof(int));
		out.write((char*)(&offer.fixed), sizeof(bool));
	}
	else {
		cout << "Name: " << offer.name << endl;
		cout << "Price: " << offer.price << endl;
	}
	return out;
}

istream& operator >> (istream& in, Offer& offer) {
	if (&in != &cin) {
		size_t len;
		in.read((char*)(&len), sizeof(size_t));
		char* str = new char[len];
		in.read(str, len);
		offer.name = str;
		delete[] str;
		in >> offer.order;
		in.read((char*)(&offer.price), sizeof(int));
		in.read((char*)(&offer.fixed), sizeof(bool));
	}
	else {
		cout << "\nName: ";
		in >> offer.name;
		cout << "Price: ";
		in >> offer.price;
	}
	return in;
}