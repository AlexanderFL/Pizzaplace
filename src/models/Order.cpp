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
	status = 0;
	//location = 0;
	homeAddress = "none";

}

Order::Order(vector<Pizza> pizzas, vector<SideOrder> sides, double totalCost, int status, Location location, string comment, string homeAddress) {
	this->pizzas = pizzas;
	this->sides = sides;
	this->totalCost = totalCost;
	this->status = status;
	this->location = location;
	this->comment = comment;
	this->homeAddress = homeAddress;
}

/*
	Prompt the user for his order, the user can select multiple pizzas and
	can change his order or cancel his order.

	TODO: Complete the Pizza class for istream input and input options UI
*/

void Order::MakeOrder()
{
	Pizza tempPizza;
	//Maybe skip the comment "New Order". Commented it out at least for now
	//cout << "New Order" << endl;
	cin >> tempPizza; // TODO: Finish this.
}

/*
	Get total cost for the order
*/
double Order::getTotalCost() {
	calculateCost();
	return totalCost;
}

/*
*************************************************
				PRIVATE FUNCTIONS
*************************************************
*/

/*
	Calculates the total cost for the order,
	Based on how many pizzas were ordered, size of them and what toppings.
*/
void Order::calculateCost() {
	totalCost = 0;
	for (unsigned int i = 0; i < pizzas.size(); ++i) {
		totalCost += pizzas.at(i).getCost();
	}
	/*
	for (unsigned int i = 0; i < sides.size(); ++i) {
		totalCost += sides.at(i).getPrice();
	}*/
}

//To get the home address of a person (TODO: fix)
void Order::setHomeAddress(string address) {
	homeAddress = address;
}

int Order::getPizzaOrderLength() const
{
	return pizzas.size();
}

int Order::getSideOrderLength() const
{
	return sides.size();
}

Pizza Order::getPizzaIndex(int index) const
{
	if (index >= 0 && index < pizzas.size()) {
		return pizzas[index];
	}
	return pizzas[0];
}

SideOrder Order::getSideOrderIndex(int index) const
{
	if (index >= 0 && index < sides.size()) {
		return sides[index];
	}
	return sides[0];
}

string Order::getHomeAddress() const {
	return homeAddress;
}
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
		int size = order.pizzas.size();
		out.write((char*)(&size), sizeof(int));
		for (int i = 0; i < size; ++i) {
			out << order.pizzas.at(i);
		}
		size = order.sides.size();
		out.write((char*)(&size), sizeof(int));
		for (int i = 0; i < size; ++i) {
			out << order.sides.at(i);
		}
		out.write((char*)(&order.totalCost), sizeof(double));
		out.write((char*)(&order.status), sizeof(int));
		out.write((char*)(&order.location), sizeof(int));
		int len = order.comment.length() + 1;
		out.write((char*)(&len), sizeof(int));
		out.write(order.comment.c_str(), len);
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
		int size;
		Pizza pizza;
		in.read((char*)(&size), sizeof(int));
		for (int i = 0; i < size; ++i) {
			in >> pizza;
			order.pizzas.push_back(pizza);
		}
		in.read((char*)(&size), sizeof(int));
		SideOrder side;
		for (int i = 0; i < size; ++i) {
			in >> side;
			order.sides.push_back(side);
		}
		in.read((char*)(&order.totalCost), sizeof(double));
		in.read((char*)(&order.status), sizeof(int));
		in.read((char*)(&order.location), sizeof(int));
		int len;
		in.read((char*)(&len), sizeof(int));
		char* str = new char[len];
		in.read(str, len);
		order.comment = str;
		delete[] str;
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
