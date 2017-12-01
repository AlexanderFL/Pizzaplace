#include <fstream>
#include "ToppingRepository.h"

ToppingRepository::ToppingRepository() {
    this->file = "toppings.dat";
}

void ToppingRepository::storeToppings(const vector<Topping> &toppings) const {
	ofstream fout;
	fout.open(this->file, ios::binary);
	int size = toppings.size();
	fout.write((char*)(&size), sizeof(int));
	for (int i = 0; i < size; ++i) {
		toppings[i].write(fout);
	}
	fout.close();
}

vector<Topping> ToppingRepository::retrieveToppings() const {
	//Todo: make sure the file isn't empty
	ifstream fin;
	Topping topping;
	fin.open(this->file, ios::binary);
	int size;
	fin.read((char*)(&size), sizeof(int));
	vector<Topping> vec;
	for (int i = 0; i < size; ++i) {
		topping.read(fin);
		vec.push_back(topping);
	}
	fin.close();
	return vec;
}

void ToppingRepository::storeTopping(const Topping& topping) const {
	vector<Topping> toppings = this->retrieveToppings();
	toppings.push_back(topping);
	this->storeToppings(toppings);
}

Topping ToppingRepository::retrieveTopping(int& loc) const {
	//Todo: make sure that loc exists
	vector<Topping> toppings = this->retrieveToppings();
	return toppings.at(loc);
}