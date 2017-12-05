#include "ManagerService.h"

ManagerService::ManagerService() {}

void ManagerService::addTopping(const Topping& topping) const {
	//Validate topping

	repo.WriteToFile(topping);
}

vector<Topping> ManagerService::getToppings() const {
	return RetrieveAllFromFile<Topping>();
}