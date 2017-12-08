#include <fstream>
#include "Order.h"

/*
*************************************************
				PUBLIC FUNCTIONS
*************************************************
*/

const string Order::filename = "orders.dat";

Order::Order() 
{ 
	totalCost = 0;
	comment = "";
	_status = PREPERATION;
	//location = 0;
	homeAddress = "none";
	_deliveryMethod = PICKUP;
	paidFor = false;
}

Order::Order(vector<Pizza> pizzas, vector<SideOrder> sides, status orderStatus, Location location, string comment, string homeAddress, deliveryMethod orderDeliveryMethod, bool isPaid) {
	this->pizzas = pizzas;
	this->sides  = sides;
	this->totalCost = totalCost;
	this->_status = orderStatus;
	this->sides = sides;
	this->_status = orderStatus;
	this->location = location;
	this->comment = comment;
	this->homeAddress = homeAddress;
	this->_deliveryMethod = orderDeliveryMethod;
	this->paidFor = isPaid;
}

vector<Pizza>  Order::getPizzas() const {
	return this->pizzas;
}

vector<SideOrder>  Order::getSides() const {
	return this->sides;
}

status Order::getStatus() const {
	return this->_status;
}

Location  Order::getLocation() const {
	return this->location;
}

string  Order::getComment() const {
	return this->comment;
}

string  Order::getHomeAddress() const {
	return this->homeAddress;
}

deliveryMethod Order::getDeliveryMethod() const
{
	return _deliveryMethod;
}

bool Order::isPaidFor() const
{
	return paidFor;
}

void  Order::setPizzas(const vector<Pizza>& pizzas) {
	this->pizzas = pizzas;
}

void  Order::setSides(const vector<SideOrder>& sides) {
	this->sides = sides;
}

void  Order::setStatus(const status& orderStatus) {
	this->_status = orderStatus;
}

void  Order::setLocation(const Location& location) {
	this->location = location;
}

void  Order::setComment(const string& comment) {
	this->comment = comment;
}

void  Order::setHomeAddress(const string& homeAddress) {
	this->homeAddress = homeAddress;
}

void Order::setDeliveryMethod(const deliveryMethod & orderDeliveryMethod)
{
	this->_deliveryMethod = orderDeliveryMethod;
}

void Order::setOrderAsPaidFor(bool isPaid)
{
	this->paidFor = isPaid;
}

/*
*************************************************
				PRIVATE FUNCTIONS
*************************************************
*/


/*
*************************************************
				OVERLOAD FUNCTIONS
*************************************************
*/

/*
	Prints the order from a user.
*/
ostream& operator <<(ostream& out, const Order& order)
{
	if (&out != &cout) {
		size_t size = order.pizzas.size();
		out.write((char*)(&size), sizeof(size_t));
		for (size_t i = 0; i < size; ++i) {
			out << order.pizzas.at(i);
		}
		size = order.sides.size();
		out.write((char*)(&size), sizeof(size_t));
		for (size_t i = 0; i < size; ++i) {
			out << order.sides.at(i);
		}
		out.write((char*)(&order._status), sizeof(status));
		out << order.location;
		size_t len = order.comment.length() + 1;
		out.write((char*)(&len), sizeof(size_t));
		out.write(order.comment.c_str(), len);
		len = order.homeAddress.length() + 1;
		out.write((char*)(&len), sizeof(size_t));
		out.write(order.homeAddress.c_str(), len);
		out.write((char*)(&order._deliveryMethod), sizeof(deliveryMethod));
	}
	else {
		out << "order";
	}
	return out;
}

istream& operator >> (istream& in, Order& order) {
	if (&in != &cin) {
		order.pizzas.clear();
		order.sides.clear();
		size_t size;
		Pizza pizza;
		in.read((char*)(&size), sizeof(size_t));
		for (size_t i = 0; i < size; ++i) {
			in >> pizza;
			order.pizzas.push_back(pizza);
		}
		in.read((char*)(&size), sizeof(size_t));
		SideOrder side;
		for (size_t i = 0; i < size; ++i) {
			in >> side;
			order.sides.push_back(side);
		}
		in.read((char*)(&order._status), sizeof(status));
		in >> order.location;
		size_t len;
		in.read((char*)(&len), sizeof(size_t));
		char* str = new char[len];
		in.read(str, len);
		order.comment = str;
		delete[] str;
		in.read((char*)(&len), sizeof(size_t));
		str = new char[len];
		in.read(str, len);
		order.homeAddress = str;
		delete[] str;
		in.read((char*)(&order._deliveryMethod), sizeof(deliveryMethod));
	}
	return in;
}

bool operator == (const Order& left, const Order& right) {
	Order order = left * right;
	return left.pizzas.size() == order.pizzas.size() && left.sides.size() == order.sides.size();
}

bool operator != (const Order& left, const Order& right) {
	return !(left == right);
}

bool operator <= (const Order& left, const Order& right) {
	Order order = left * right;
	return left == order;
}

Order operator * (const Order& left, const Order& right) {
	Order order;
	for (int i = 0; i < left.pizzas.size(); ++i) {
		for (int j = 0; j < right.pizzas.size(); ++j) {
			if (left.pizzas.at(i) == right.pizzas.at(j)) {
				order.pizzas.push_back(left.pizzas.at(i));
				break;
			}
		}
	}
	for (int i = 0; i < left.sides.size(); ++i) {
		for (int j = 0; j < right.sides.size(); ++j) {
			if (left.sides.at(i) == right.sides.at(j)) {
				order.sides.push_back(left.sides.at(i));
				break;
			}
		}
	}
	return order;
}

// The + operator ONLY adds together the vectors pizzas and sides
Order operator + (const Order& left, const Order& right) {
	Order newOrder;
	// Copy left Order into newOrder
	newOrder = left;

	// Append right pizzas together into newOrder
	for (int i = 0; i < right.pizzas.size(); i++) {
		newOrder.pizzas.push_back(right.pizzas[i]);
	}

	// Append right side orders into newOrder
	for (int i = 0; i < left.sides.size(); i++) {
		newOrder.sides.push_back(left.sides[i]);
	}
	
	return newOrder;
}