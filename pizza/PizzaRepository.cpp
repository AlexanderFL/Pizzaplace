#include <fstream>
#include "PizzaRepository.h"

PizzaRepository::PizzaRepository() {
    this->file = "pizzas.dat";
}

/*
	todo: Do the storing and retrieving of pizzas
*/

void PizzaRepository::storePizza(const Pizza &pizza) const {
    ofstream fout;
    fout.open(this->file, ios::binary | ios::app);
    //pizza.write(fout);
    fout.close();
}

Pizza PizzaRepository::retrievePizza() const {
    ifstream fin;
    Pizza pizza;
    fin.open(this->file, ios::binary);
    //pizza.read();
    fin.close();
    return pizza;
}