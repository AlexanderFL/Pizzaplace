#pragma once
#include <iostream>
#include <string>
#include "KitchenService.h"
#include "CommonUI.h"
using namespace std;

class KitchenUI: public CommonUI
{
private: 
	KitchenService service;
public:
	KitchenUI();
	void kitchenMenu();
	string showPizzaInfo(const Pizza& pizza) const;
	string showPizzaInfoShort(const Pizza& pizza) const;
};

