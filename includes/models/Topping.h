#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Topping
{
public:
	static const string filename;
private:
	string name;
	int price;

public:
	Topping();
	Topping(string name, int price);
	vector<Topping> getAllToppings();
	double getPrice() const;
	string getName() const;
	friend istream& operator >> (istream& in, Topping& topping);
	friend ostream& operator << (ostream& out, const Topping& topping);
	friend bool operator == (const Topping& left, const Topping& right);
};
