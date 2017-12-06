#include "Offer.h"

Offer::Offer(string offername, Order order)
	:_offername(offername), _order(order)
{
}

string Offer::getOffername() {
	return _offername;
}

Order Offer::getOrder() {
	return _order;
}