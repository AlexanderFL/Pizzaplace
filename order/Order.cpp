#include <fstream>
#include "Order.h"

/*
	PUBLIC FUNCTIONS
*/

Order::Order() 
{ 
	totalCost = 0;
}

void Order::MakeOrder()
{
	Pizza tempPizza;
	cout << "New Order" << endl;
	cin >> tempPizza;
}

void Order::write(ofstream& fout) const {
	int size = this->pizzas.size();
	fout.write((char*)(&size), sizeof(int));
	for (int i = 0; i < size; ++i) {
		pizzas[i].write(fout);
	}
	fout.write((char*)(&this->totalCost), sizeof(double));
}

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

double Order::getTotalCost() {
	this->calculateCost();
	return this->totalCost;
}

/*
	PRIVATE FUNCTIONS
*/

void Order::calculateCost() {
	this->totalCost = 0;
	for (int i = 0; i < pizzas.size(); ++i) {
		this->totalCost += pizzas[i].getCost();
	}
}

/*
FRIEND FUNCTIONS
*/

ostream& operator<<(ostream& out, const Order& order)
{
	out << order;

	return out;
}