#include "ManagerService.h"

ManagerService::ManagerService() {}

void ManagerService::addTopping(const Topping& topping) {
	//Validate topping

	repo.WriteToFile(topping);
}

void ManagerService::addSideOrder(const SideOrder& side) {
	//Validate sideorder

	//repo.WriteTofile(side);
}

vector<Topping> ManagerService::getToppings() {
	return repo.RetrieveAllFromFile<Topping>();
}