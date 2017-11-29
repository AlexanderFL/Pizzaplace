//
// Created by Thomas Ari Bech on 29.11.17.
//

#ifndef PIZZAPLACE_TOPPINGREPOSITORY_H
#define PIZZAPLACE_TOPPINGREPOSITORY_H

#include "Topping.h"

class ToppingRepository {
    private:
        string file;
    public:
        ToppingRepository();
        void storeTopping(const Topping& topping) const;
        Topping retrieveTopping() const;
};


#endif //PIZZAPLACE_TOPPINGREPOSITORY_H
