#include <fstream>
#include "Pizza.h"

/*
*************************************************
				PUBLIC FUNCTIONS
*************************************************
*/

Pizza::Pizza() {
	this->size = 0;
	this->cost = 0;
}

/*
	Writes the pizza to a binary file
*/
void Pizza::write(ofstream& fout) const {
	int size = this->nrToppings();
	fout.write((char*)(&size), sizeof(int));
	for (int i = 0; i < this->nrToppings(); ++i) {
		toppings.at(i).write(fout);
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
		this->addTopping(topping);
	}
	fin.read((char*)(&this->size), sizeof(int));
	fin.read((char*)(&this->cost), sizeof(double));
}

/*
	Add a topping to the toppings vector
*/
void Pizza::addTopping(const Topping& top) {
	this->toppings.push_back(top);
}

/*
	Returns the number of toppings in the pizza
*/
int Pizza::nrToppings() const {
	return this->toppings.size();
}

/*
	Returns the cost of the pizza
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

/*
	Calculates the cost for the pizza and sets the price of the pizza
*/
void Pizza::calculateCost() {
	this->cost = 0;
	for (int i = 0; i < this->nrToppings(); ++i) {
		this->cost += toppings.at(i).getPrice();
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
	for (int i = 0; i < pizza.nrToppings(); ++i) {
		out << pizza.toppings.at(i) << " ";
	}
	return out;
}

istream& operator>> (istream& in, Pizza& pizza)
{
	// TODO: Make this a function call to UI layer
	int size;
	do {
		cout << "Select pizza size:" << endl;
		cout << " 1: Small\t\t950kr.-"  << endl;
		cout << " 2: Medium\t\t1150kr.-" << endl;
		cout << " 3: Large\t\t1450kr.-" << endl;
		cout << " Insert number: ";
		in >> size;
	} while (size < 1 || 3 < size);
	pizza.size = size;

	cout << "Select toppings: " << endl;

	for (int i = 0; i < pizza.nrToppings(); i++)
	{

	}
	return in;
}

/*
	Compares whether the two pizzas have the same toppings
*/
bool operator == (const Pizza& left, const Pizza& right) {
	if (left.size == right.size) {
		Pizza pizza = left * right;
		if (pizza.nrToppings() == left.nrToppings() && pizza.nrToppings() == right.nrToppings()) {
			return true;
		}
	}
	return false;
}

/*
	Compares whether the two pizzas do not have the same toppings
*/
bool operator != (const Pizza& left, const Pizza& right) {
	return !(left == right);
}

/*
	Returns a pizza with the intersection for the toppings of two Pizzas
*/
Pizza operator * (const Pizza& left, const Pizza& right) {
	Pizza pizza;
	for (int i = 0; i < left.nrToppings(); ++i) {
		for (int j = 0; j < right.nrToppings(); ++j) {
			if (left.toppings.at(i) == right.toppings.at(j)) {
				pizza.addTopping(left.toppings.at(i));
				break;
			}
		}
	}
	return pizza;
}

/*
	Returns a pizza with the compenation for the toppings of two Pizzas
*/
Pizza operator + (const Pizza& left, const Pizza& right) {
	Pizza pizza = left;
	for (int i = 0; i < right.nrToppings(); ++i) {
		pizza.addTopping(right.toppings.at(i));
	}
	return pizza;
}