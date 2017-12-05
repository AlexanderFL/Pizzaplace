#include <iostream>

#include "Data.h"

using namespace std;
#include "MainUI.h"

int main()
{
	//MainUI mainUI;
	//mainUI.startUI();

	Data d;

	Topping t("Shoelace", 450);
	Topping t1("Another one", 700);

	vector<Topping> all = d.RetrieveAllFromFile<Topping>();
	
	for (int i = 0; i < all.size(); i++)
	{
		cout << i+1 << ": " << all[i] << endl;
	}

	d.ModifyFileAtIndex<Topping>(5);
	all = d.RetrieveAllFromFile<Topping>();

	cout << endl;

	for (int i = 0; i < all.size(); i++)
	{
		cout << i + 1 << ": " << all[i] << endl;
	}

	system("PAUSE");

	return 0;
}