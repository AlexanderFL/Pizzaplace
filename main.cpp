#include <iostream>

#include "data/Data.h"

using namespace std;
#include "ui/MainUI.h"

int main()
{
	//MainUI mainUI;
	//mainUI.startUI();

	Topping t("Ananas", 350);

	Data d;
	d.WriteToFile(t);

	system("PAUSE");

	return 0;
}