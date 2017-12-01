#include <iostream>

#include "data/Data.h"

using namespace std;
#include "ui/MainUI.h"

int main()
{
	//MainUI mainUI;
	//mainUI.startUI();

	Topping t1("Ananas", 350);
	Topping t2("Pepperoni", 400);

	vector<Topping> vec;
	vec.push_back(t1);
	vec.push_back(t2);
	Data d;

	d.WriteMultipleLinesToFile(vec);

	Topping top = d.RetrieveFromFile<Topping>(1);
	cout << top;

	system("PAUSE");

	return 0;
}