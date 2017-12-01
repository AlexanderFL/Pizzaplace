#include <fstream>
#include "ToppingRepository.h"

ToppingRepository::ToppingRepository() {
    file = "toppings.dat";
}

void ToppingRepository::storeToppings(const vector<Topping> &toppings) const {
	ofstream fout;
	fout.open(file, ios::binary);
	int size = toppings.size();
	fout.write((char*)(&size), sizeof(int));
	for (int i = 0; i < size; ++i) {
		toppings.at(i).write(fout);
	}
	fout.close();
}

vector<Topping> ToppingRepository::retrieveToppings() const {
	vector<Topping> vec;
	ifstream fin;
	Topping topping;
	fin.open(file, ios::binary);
	if (fin.is_open()) {
		fin.seekg(0, fin.end);
		int endpos = fin.tellg();
		if (endpos != 0) {
			fin.seekg(0);
			int size;
			fin.read((char*)(&size), sizeof(int));
			for (int i = 0; i < size; ++i) {
				topping.read(fin);
				vec.push_back(topping);
			}
		}
		fin.close();	}
	return vec;
}

void ToppingRepository::storeTopping(const Topping& topping) const {
	vector<Topping> toppings = retrieveToppings();
	toppings.push_back(topping);
	storeToppings(toppings);
}

Topping ToppingRepository::retrieveTopping(int& loc) const {
	//Todo: make sure that loc exists
	vector<Topping> toppings = this->retrieveToppings();
	return toppings.at(loc);
}