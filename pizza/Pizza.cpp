#include <fstream>
#include <cmath>
#include "Pizza.h"

/*
*************************************************
				PUBLIC FUNCTIONS
*************************************************
*/

Pizza::Pizza() {}

/*
	Writes the pizza to a binary file
*/
void Pizza::write(ofstream& fout) const {
	int size = this->toppings.size();
	fout.write((char*)(&size), sizeof(int));
	for (int i = 0; i < toppings.size(); ++i) {
		toppings[i].write(fout);
	}
	fout.write((char*)(&this->size), sizeof(int));
	fout.write((char*)(&this->cost), sizeof(double));
}

/*
	Reads the pizza from a binary file
*/
void Pizza::read(ifstream& fin) {
	int size;
	fin.read((char*)(&size), sizeof(int));
	this->toppings.clear();
	Topping topping;
	for (int i = 0; i < size; ++i) {
		topping.read(fin);
		this->toppings.push_back(topping);
	}
	fin.read((char*)(&this->size), sizeof(int));
	fin.read((char*)(&this->cost), sizeof(double));
}

/*
	Calculates the cost for the pizza.
*/
double Pizza::getCost() {
	this->calculateCost();
	return this->cost;
}

/*
*************************************************
*****			PRIVATE FUNCTIONS			*****
*************************************************
*/

void Pizza::calculateCost() {
	this->cost = 0;
	for (int i = 0; i < this->toppings.size(); ++i) {
		this->cost += toppings[i].getPrice();
	}
	if (size == 1) {
		this->cost += 950;
	} else if (size == 2) {
		this->cost += 1150;
	} else if (size == 3) {
		this->cost += 1450;
	}
}

/*
*************************************************
				FRIEND FUNCTIONS
*************************************************
*/
ostream& operator<< (ostream& out, const Pizza& pizza)
{
	return out;
}

istream& operator>> (istream& in, Pizza& pizza)
{
	// TODO: Make this a function call to UI layer

	cout << "Select pizza size:" << endl;
	cout << " 1: Small\t\t950kr.-" << endl;
	cout << " 2: Medium\t\t1150kr.-" << endl;
	cout << " 3: Large\t\t1450kr.-" << endl;
	cout << " Insert number: ";
	in >> pizza.size;

	cout << "Select toppings: " << endl;

	for (int i = 0; i < pizza.toppings.size(); i++)
	{

	}
	return in;
}

bool operator == (const Pizza& left, const Pizza& right) {
	Pizza pizza;
	for (unsigned int i = 0; i < left.toppings.size(); ++i) {
		for (unsigned int j = 0; j < right.toppings.size(); ++j) {
			if (left.toppings.at(i) == right.toppings.at(j)) {
				pizza.toppings.push_back(left.toppings.at(i));
			}
		}
	}
	if (pizza.toppings.size() == left.toppings.size() && pizza.toppings.size() == right.toppings.size()) {
		return true;
	}
	return false;
}