//
// Created by Thomas Ari Bech on 29.11.17.
//

#include <fstream>
#include "PizzaRepository.h"

PizzaRepository::PizzaRepository() {
    this->file = "pizzas.dat";
}

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