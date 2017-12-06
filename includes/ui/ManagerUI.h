#include <iostream>
#include <string>
#include <algorithm>
#include "ManagerService.h"
using namespace std;

class ManagerUI
{
private:
	char input;
	ManagerService service;
public:
	ManagerUI();
	void managerMenu();
	void validateToppingInput(char input);
	void addTopping();
	void deleteTopping();
};

