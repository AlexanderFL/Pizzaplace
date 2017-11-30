#include <fstream>
#include "ToppingRepository.h"

ToppingRepository::ToppingRepository() {
    this->file = "toppings.dat";
}

/*
	todo: Do the storing and retrieving of toppings
*/

void ToppingRepository::storeTopping(const Topping &topping) const {
    ofstream fout;
    fout.open(this->file, ios::binary | ios::app);
    //topping.write(fout);
    fout.close();
}

Topping ToppingRepository::retrieveTopping() const {
    ifstream fin;
    Topping topping;
    fin.open(this->file, ios::binary);
    //topping.read();
    fin.close();
    return topping;
}