#ifndef PIZZAREPOSITORY_H
#define PIZZAREPOSITORY_H

#include "Pizza.h"

class PizzaRepository {
    private:
        string file;
    public:
        PizzaRepository();
        void storePizza(const Pizza& pizza) const;
        Pizza retrievePizza() const;
};


#endif //PIZZAREPOSITORY_H
