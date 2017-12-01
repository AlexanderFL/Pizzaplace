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

	vector<Topping> vec2;
	vec2 = d.RetrieveAllFromFile<Topping>();

	for (int i = 0; i < vec2.size(); i++)
	{
		cout << vec2[i] << endl;
	}

	system("PAUSE");

	return 0;
}