#include <fstream>
#include "OrderRepository.h"

OrderRepository::OrderRepository() {
    file = "orders.dat";
}

void OrderRepository::storeOrders(const vector<Order> &orders) const {
    ofstream fout;
    fout.open(file, ios::binary);
	int size = orders.size();
	fout.write((char*)(&size), sizeof(int));
	for (int i = 0; i < size; ++i) {
		orders.at(i).write(fout);
	}
    fout.close();
}

vector<Order> OrderRepository::retrieveOrders() const {
	vector<Order> vec;
    ifstream fin;
    Order order;
    fin.open(file, ios::binary);
	if (fin.is_open()) {
		fin.seekg(0, fin.end);
		int endpos = fin.tellg();
		if (endpos != 0) {
			fin.seekg(0);
			int size;
			fin.read((char*)(&size), sizeof(int));
			for (int i = 0; i < size; ++i) {
				order.read(fin);
				vec.push_back(order);
			}
		}
		fin.close();
	}
    return vec;
}

void OrderRepository::storeOrder(const Order& order) const {
	vector<Order> orders = retrieveOrders();
	orders.push_back(order);
	storeOrders(orders);
}

Order OrderRepository::retrieveOrder(int& loc) const {
	//Todo: make sure that loc exists
	vector<Order> orders = retrieveOrders();
	return orders.at(loc);
}