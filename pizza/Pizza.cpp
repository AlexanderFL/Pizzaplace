#include <fstream>
#include "Pizza.h"

Pizza::Pizza()
{
	this->toppings = nullptr;
	this->nrOfToppings = 0;
}

Pizza::Pizza(int numberOfToppings)
{
	this->toppings = nullptr;
	this->nrOfToppings = numberOfToppings;
}

Pizza::~Pizza() {
	if (this->toppings != nullptr) {
		delete[] toppings;
	}
}

void Pizza::write(ofstream& fout) const {
	fout.write((char*)(&this->nrOfToppings), sizeof(int));
	for (int i = 0; i < nrOfToppings; ++i) {
		toppings[i].write(fout);
	}
	fout.write((char*)(&this->size), sizeof(int));
	fout.write((char*)(&this->cost), sizeof(int));
}

void Pizza::read(ifstream& fin) {
	fin.read((char*)(&this->nrOfToppings), sizeof(int));
	if (this->toppings != nullptr) {
		delete[] toppings;
	}
	toppings = new Topping[this->nrOfToppings];
	for (int i = 0; i < this->nrOfToppings; ++i) {
		toppings[i].read(fin);
	}
	fin.read((char*)(&this->size), sizeof(int));
	fin.read((char*)(&this->cost), sizeof(int));
}

ostream& operator<< (ostream& out, const Pizza& pizza)
{
	out << pizza.toppings;

	return out;
}

istream& operator>> (istream& in, Pizza& pizza)
{
	cout << "Select pizza size:" << endl;
	cout << " 1: Small\t\t950kr.-" << endl;
	cout << " 2: Medium\t\t1150kr.-" << endl;
	cout << " 3: Large\t\t1450kr.-" << endl;
	cout << " Insert number: ";
	in >> pizza.size;

	cout << "Select toppings: " << endl;

	// TODO: change i < x, to corrisponding topping number
	for (int i = 0; i < 10; i++)
	{

	}
	return in;
}