//
// Created by Thomas Ari Bech on 29.11.17.
//

#ifndef PIZZAPLACE_PIZZAREPOSITORY_H
#define PIZZAPLACE_PIZZAREPOSITORY_H

#include "Pizza.h";

class PizzaRepository {
    private:
        string file;
    public:
        PizzaRepository();
        void storePizza(const Pizza& pizza) const;
        Pizza retrievePizza() const;
};


#endif //PIZZAPLACE_PIZZAREPOSITORY_H
