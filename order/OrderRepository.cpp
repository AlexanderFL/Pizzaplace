#include <fstream>
#include "OrderRepository.h"

OrderRepository::OrderRepository() {
    this->file = "orders.dat";
}

void OrderRepository::storeOrders(const vector<Order> &orders) const {
    ofstream fout;
    fout.open(this->file, ios::binary);
	int size = orders.size();
	fout.write((char*)(&size), sizeof(int));
	for (int i = 0; i < size; ++i) {
		orders[i].write(fout);
	}
    fout.close();
}

vector<Order> OrderRepository::retrieveOrders() const {
    ifstream fin;
    Order order;
    fin.open(this->file, ios::binary);
	int size;
	fin.read((char*)(&size), sizeof(int));
	vector<Order> vec;
	for (int i = 0; i < size; ++i) {
		order.read(fin);
		vec.push_back(order);
	}
    fin.close();
    return vec;
}