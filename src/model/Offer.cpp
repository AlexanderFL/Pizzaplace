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
		
	}
	return out;
}

istream& operator >> (istream& in, Offer& offer) {
	if (&in != &cin) {

	}
	return in;
}