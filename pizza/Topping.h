#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Topping
{
private:
	string name;
	double price;
public:
	Topping();

	void NewTopping(string name, double price);
	vector<Topping> getAllToppings();
	void write(ofstream& fout) const;
	void read(ifstream& fin);
	double getPrice();

	friend ostream& operator << (ostream& out, const Topping topping);
};
