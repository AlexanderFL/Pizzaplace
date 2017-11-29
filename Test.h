//
// Created by Thomas Ari Bech on 29.11.17.
//

#ifndef PIZZAPLACE_TEST_H
#define PIZZAPLACE_TEST_H

#include <iostream>
#include <string>
using namespace std;

class Test {
    private:
        string name;
        double d;
        int* point;
        int size;
    public:
        Test();
        Test(string name, double d, int size);
        void read(ifstream& fin);
        void write(ofstream& fout) const;
        friend ostream& operator << (ostream& out, const Test& test);
};


#endif //PIZZAPLACE_TEST_H
