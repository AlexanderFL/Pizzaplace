#include "Offer.h"
#include <fstream>

const string Offer::filename = "offers.dat";

Offer::Offer() {
	_price = 0;
	_fixed = true;
}

Offer::Offer(string offername, Order order, int price, bool fixed)
	:_offername(offername), _order(order), _price(price), _fixed(fixed)
{
}

string Offer::getOffername() {
	return _offername;
}

Order Offer::getOrder() {
	return _order;
}

ostream& operator << (ostream& out, const Offer& offer) {
	if (&out != &cout) {
		int len = offer._offername.length() + 1;
		out.write((char*)(&len), sizeof(int));
		out.write(offer._offername.c_str(), len);
		out << offer._order;
		out.write((char*)(&offer._price), sizeof(int));
		out.write((char*)(&offer._fixed), sizeof(bool));
	}
	return out;
}

istream& operator >> (istream& in, Offer& offer) {
	if (&in != &cin) {
		int len;
		in.read((char*)(&len), sizeof(int));
		char* str = new char[len];
		in.read(str, len);
		offer._offername = str;
		delete[] str;
		in >> offer._order;
		in.read((char*)(&offer._price), sizeof(int));
		in.read((char*)(&offer._fixed), sizeof(bool));
	}
	return in;
}