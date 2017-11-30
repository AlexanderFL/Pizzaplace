#include <fstream>
#include "Test.h"

Test::Test() {
    this->name = "OwO";
    this->d = 123.456;
    this->point = new int[8];
    for (int i = 0; i < 8; ++i) {
        point[i] = i;
    }
    this->size = 8;
}

Test::Test(string name, double d, int size) {
    this->name = name;
    this->d = d;
    this->point = new int[size];
    for (int i = 0; i < size; ++i) {
        point[i] = i;
    }
    this->size = size;
}

void Test::write(ofstream& fout) const {
    int len = this->name.length();
    fout.write((char*)(&len), sizeof(int));
    for (int i = 0; i < len; ++i) {
        fout.write((char*)(&this->name[i]), sizeof(char));
    }
    fout.write((char*)(&this->d), sizeof(double));
    fout.write((char*)(&this->size), sizeof(int));
    fout.write((char*)(this->point), sizeof(int) * size);
}

void Test::read(ifstream& fin) {
    int len;
    this->name = "";
    char n;
    fin.read((char*)(&len), sizeof(int));
    for (int i = 0; i < len; ++i) {
        fin.read(&n, sizeof(char));
        this->name += n;
    }
    fin.read((char*)(&this->d), sizeof(double));
    fin.read((char*)(&this->size), sizeof(int));
    this->point = new int[size];
    fin.read((char*)(this->point), sizeof(int) * size);
}

ostream& operator << (ostream& out, const Test& test) {
    out << test.name << " " << test.d << " ";
    for (int i = 0; i < test.size; ++i) {
        out << test.point[i];
    }
    out << endl;
    return out;
}
