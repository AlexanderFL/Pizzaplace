#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "../pizza/Topping.h"
#include "../order/Order.h"
using namespace std;

class Data
{
public:
	template <class Repos>
	void WriteToFile(Repos r);

	void WriteMultipleLinesToFile(vector<Topping> t);
	void WriteMultipleLinesToFile(vector<Order> o);

private:
	void Write(Topping t);
};

template<class Repos>
inline void Data::WriteToFile(Repos r)
{
	ofstream fout;
	fout.open(r.filename, ios::binary);
	r.write(fout);
	fout.close();
}
