#ifndef ORDERREPOSITORY_H
#define ORDERREPOSITORY_H

#include <vector>
#include "Order.h"

class OrderRepository {
    private:
        string file;
    public:
        OrderRepository();
        void storeOrders(const vector<Order> &orders) const;
        vector<Order> retrieveOrders() const;
		void storeOrder(const Order& order) const;
		Order retrieveOrder(int& loc) const;
};


#endif //ORDERREPOSITORY_H
