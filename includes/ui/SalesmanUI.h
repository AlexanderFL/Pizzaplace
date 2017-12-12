#include <iostream>
#include <string>
#include <algorithm>
#include "CommonUI.h"
#include "SalesmanService.h"
using namespace std;

class SalesmanUI: public CommonUI
{
private:
	SalesmanService service;
public:
	SalesmanUI();
	void salesmanMenu();
	void makeNewOrder();
	void pickFromMenu();
};


