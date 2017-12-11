#pragma once
#include <iostream>
#include <string>
#include "KitchenService.h"
using namespace std;

class KitchenUI
{
private: 
	KitchenService service;
public:
	KitchenUI();
	void kitchenMenu();
	string showPizzaInfo(const Pizza& pizza) const;
	string showPizzaInfoShort(const Pizza& pizza) const;
};

