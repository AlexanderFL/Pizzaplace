#include <iostream>
#include <string>
#include <algorithm>
#include "ManagerService.h"
using namespace std;

class ManagerUI
{
private:
	char input;
	ManageService service;
public:
	ManagerUI();
	void managerMenu();
	void validateToppingInput(char input);
	void addTopping();
	void deleteTopping();
};

