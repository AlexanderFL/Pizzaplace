#pragma once

#include <iostream>
#include <string>

using namespace std;

class SideOrder {
public:
	static const string filename;
private:
	string name;
	int price;

public:
	SideOrder();
	SideOrder(string name, int price);
	string getName() const;
	double getPrice() const;
	void setName(const string& name);
	void setPrice(const int& price);
	friend ostream& operator<< (ostream& out, const SideOrder& side);
	friend istream& operator>> (istream& in, SideOrder& side);
	friend bool operator == (const SideOrder& left, const SideOrder& right);
};

