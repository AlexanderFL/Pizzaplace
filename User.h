#pragma once
#include <iostream>
#include <string>
using namespace std;

class User
{
private:
	string name;
	int level;
public:
	User(string name, int level);
	User(int level);
	User();


};

