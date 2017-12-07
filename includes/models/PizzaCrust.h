#pragma once

#include <iostream>
#include <string>

using namespace std;

class PizzaCrust
{
public:
	static const string filename;
private:
	string name;
	int price;
public:
	PizzaCrust();
	PizzaCrust(string name, int price);
	string getName() const;
	int getPrice() const;
	void setName(const string& name);
	void setPrice(const int& price);
	friend ostream& operator << (ostream& out, const PizzaCrust& crust);
	friend istream& operator >> (istream& in, PizzaCrust& crust);
};

