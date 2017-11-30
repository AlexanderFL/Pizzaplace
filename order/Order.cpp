#include <fstream>
#include "Order.h"

/*
*************************************************
				PUBLIC FUNCTIONS
*************************************************
*/

Order::Order() 
{ 
	totalCost = 0;
}

/*
	Prompt the user for his order, the user can select multiple pizzas and
	can change his order or cancel his order.

	TODO: Complete the Pizza class for istream input and input options UI
*/
void Order::MakeOrder()
{
	Pizza tempPizza;
	cout << "New Order" << endl;
	cin >> tempPizza; // TODO: Finish this.
}

/*
	Writes the user order to a binary file after the user has completed his order
*/
void Order::write(ofstream& fout) const {
	int size = this->pizzas.size();
	fout.write((char*)(&size), sizeof(int));
	for (int i = 0; i < size; ++i) {
		pizzas[i].write(fout);
	}
	fout.write((char*)(&this->totalCost), sizeof(double));
}

/*
	Reads the user order from a binary file, which can be read from the kitchen
*/
void Order::read(ifstream& fin) {
	this->pizzas.clear();
	int size;
	Pizza pizza;
	fin.read((char*)(&size), sizeof(int));
	for (int i = 0; i < size; ++i) {
		pizza.read(fin);
		this->pizzas.push_back(pizza);
	}
	fin.read((char*)(&this->totalCost), sizeof(double));
}

/*
	Get total cost for the order
*/
double Order::getTotalCost() {
	this->calculateCost();
	return this->totalCost;
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
	this->totalCost = 0;
	for (int i = 0; i < pizzas.size(); ++i) {
		this->totalCost += pizzas[i].getCost();
	}
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
	out << order;

	return out;
}