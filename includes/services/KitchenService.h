#pragma once

#include "CommonService.h"
#include "Order.h"

class KitchenService: public CommonService
{
private:
	Data repo;
public:
	KitchenService();
	//Sets the pizza of the ID as baking
	void setPizzaAsBaking(const size_t& id);
	//Sets the pizza of the ID as ready and the 
	//order as ready too if all of its pizzas are ready
	void setPizzaAsReady(const size_t& id);
	//Gets all the pizzas that are in preperation and need
	//to be baked or made ready
	vector<Pizza> getPizzas(const Location& location);
};