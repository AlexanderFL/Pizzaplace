#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class ManagerUI
{
private:
	char input;
public:
	ManagerUI();
	void managerMenu();
	void validateToppingInput(char input);
	void addTopping();
	void deleteTopping();
};

