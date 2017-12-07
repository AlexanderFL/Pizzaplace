#pragma once

#include "Data.h"
#include "User.h"
#include "InvalidLogin.h"
#include "EmptyVector.h"

class LoginService
{
private:
	Data repo;
public:
	LoginService();
	profession login(string username, string password);
	void checkForUsers();
};

