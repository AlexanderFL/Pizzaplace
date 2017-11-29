//
// Created by Thomas Ari Bech on 29.11.17.
//

#include <fstream>
#include "OrderRepository.h"

OrderRepository::OrderRepository() const {
    this->file = "orders.dat";
}

void OrderRepository::storeOrder(const Order &order) const {
    ofstream fout;
    fout.open(this->file, ios::binary | ios::app);
    order.write(fout);
    fout.close();
}

Order OrderRepository::retrieveOrder() const {
    ifstream fin;
    Order order;
    fin.open(this->file, ios::binary);
    order.read();
    fin.close();
    return order;
}