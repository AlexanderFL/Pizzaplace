#include <fstream>
#include "Order.h"

/*
*************************************************
				PUBLIC FUNCTIONS
*************************************************
*/

Order::Order() 
{ 
	this->totalCost = 0;
	this->comment = "";
	this->status = 0;
	this->location = 0;

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
		pizzas.at(i).write(fout);
	}
	size = this->sides.size();
	fout.write((char*)(&size), sizeof(int));
	for (int i = 0; i < size; ++i) {
		sides.at(i).write(fout);
	}
	fout.write((char*)(&this->totalCost), sizeof(double));
	fout.write((char*)(&this->status), sizeof(int));
	fout.write((char*)(&this->location), sizeof(int));
	int len = this->comment.length() + 1;
	fout.write((char*)(&len), sizeof(int));
	fout.write(this->comment.c_str(), len);
}

/*
	Reads the user order from a binary file, which can be read from the kitchen
*/
void Order::read(ifstream& fin) {
	this->pizzas.clear();
	this->sides.clear();
	int size;
	Pizza pizza;
	fin.read((char*)(&size), sizeof(int));
	for (int i = 0; i < size; ++i) {
		pizza.read(fin);
		this->pizzas.push_back(pizza);
	}
	fin.read((char*)(&size), sizeof(int));
	SideOrder side;
	for (int i = 0; i < size; ++i) {
		side.read(fin);
		this->sides.push_back(side);
	}
	fin.read((char*)(&this->totalCost), sizeof(double));
	fin.read((char*)(&this->status), sizeof(int));
	fin.read((char*)(&this->location), sizeof(int));
	int len;
	fin.read((char*)(&len), sizeof(int));
	char* str = new char[len];
	fin.read(str, len);
	this->comment = str;
	delete[] str;
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
		this->totalCost += pizzas.at(i).getCost();
	}
	for (int i = 0; i < sides.size(); ++i) {
		this->totalCost += sides.at(i).getPrice();
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