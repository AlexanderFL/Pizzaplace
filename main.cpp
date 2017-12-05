#include <iostream>

#include "Data.h"

using namespace std;
#include "MainUI.h"

int main()
{
	MainUI mainUI;
	mainUI.startUI();

	/*Topping t1("Ananas", 350);
	Topping t2("Pepperoni", 400);
	Topping t3("Spinach", 345);

	vector<Topping> vec;
	vec.push_back(t1);
	vec.push_back(t2);
	Data d;

	d.WriteMultipleLinesToFile(vec);
	d.WriteToFile(t3);

	Topping top = d.RetrieveFromFile<Topping>(2);
	cout << top;

	system("PAUSE");*/

	return 0;
}