//
// Created by Thomas Ari Bech on 29.11.17.
//

#ifndef PIZZAPLACE_ORDERREPOSITORY_H
#define PIZZAPLACE_ORDERREPOSITORY_H

#include "Order.h"

class OrderRepository {
    private:
        string file;
    public:
        OrderRepository();
        void storeOrder(const Order& order) const;
        Order retrieveOrder() const;
};


#endif //PIZZAPLACE_ORDERREPOSITORY_H
