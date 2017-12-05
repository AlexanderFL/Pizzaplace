#pragma once
#include <iostream>
#include <string>

using namespace std;

class SideOrder {
public:
	static const string filename;
private:
	string name;
	double price;

public:
	SideOrder();
	SideOrder(string name, double price);
	void write(ofstream& fout) const;
	void read(ifstream& fin);
	string getName() const;
	double getPrice() const;
	friend ostream& operator<< (ostream& out, const SideOrder& side);
	friend istream& operator>> (istream& out, SideOrder& side);
	friend bool operator == (const SideOrder& left, const SideOrder& right);
};

