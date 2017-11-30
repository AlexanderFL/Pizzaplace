#ifndef ORDERREPOSITORY_H
#define ORDERREPOSITORY_H

#include "Order.h"

class OrderRepository {
    private:
        string file;
    public:
        OrderRepository();
        void storeOrder(const Order& order) const;
        Order retrieveOrder() const;
};


#endif //ORDERREPOSITORY_H
