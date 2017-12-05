#pragma once

#include "Data.h"

class ManagerService
{
private:
	Data repo;
public:
	ManagerService();
	void addTopping(const Topping& topping) const;
	vector<Topping> getToppings() const;
};

