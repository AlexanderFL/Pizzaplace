#pragma once
#include <iostream>
#include <string>

using namespace std;

class Topping
{
private:
	string name;
	double price;
public:
	Topping();

	void NewTopping(string name, double price);
	Topping* getAllToppings();

	friend ostream& operator << (ostream& out, const Topping topping);
};
