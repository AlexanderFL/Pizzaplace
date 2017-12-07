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

string Offer::getOffername() {
	return name;
}

Order Offer::getOrder() {
	return order;
}

ostream& operator << (ostream& out, const Offer& offer) {
	if (&out != &cout) {
		int len = offer.name.length() + 1;
		out.write((char*)(&len), sizeof(int));
		out.write(offer.name.c_str(), len);
		out << offer.order;
		out.write((char*)(&offer.price), sizeof(int));
		out.write((char*)(&offer.fixed), sizeof(bool));
	}
	return out;
}

istream& operator >> (istream& in, Offer& offer) {
	if (&in != &cin) {
		int len;
		in.read((char*)(&len), sizeof(int));
		char* str = new char[len];
		in.read(str, len);
		offer.name = str;
		delete[] str;
		in >> offer.order;
		in.read((char*)(&offer.price), sizeof(int));
		in.read((char*)(&offer.fixed), sizeof(bool));
	}
	return in;
}