#include <iostream>
#include <string>
#include <algorithm>
#include "Menu.h"
#include "SalesmanService.h"
using namespace std;

class SalesmanUI
{
private:
	SalesmanService service;
public:
	SalesmanUI();
	void salesmanMenu();
	void makeNewOrder();
	void pickFromMenu();
};


