//
// Created by Thomas Ari Bech on 29.11.17.
//

#include <fstream>
#include "TestRepo.h"

TestRepo::TestRepo() {
    this->file = "test.dat";
}

void TestRepo::storeTest(const vector<Test>& test) const {
    ofstream fout;
    int size = test.size();
    fout.open(this->file, ios::binary);
    fout.write((char*)(&size), sizeof(int));
    for (int i = 0; i < size; ++i) {
        test[i].write(fout);
    }
    fout.close();
}

vector<Test> TestRepo::retrieveTest() const {
    ifstream fin;
    Test test;
    vector<Test> vec;
    int size;
    fin.open(this->file, ios::binary);
    fin.read((char*)(&size), sizeof(int));
    for (int i = 0; i < size; ++i) {
        test.read(fin);
        vec.push_back(test);
    }
    fin.close();
    return vec;
}