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
	User();
	User(int level);
	User(string name, int level);
};

