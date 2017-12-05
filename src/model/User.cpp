#include "User.h"

User::User(string name, int level)
{
	this->name = name;
	this->level = level;
}

User::User(int level)
{
	this->level = level;
}

User::User() { }
