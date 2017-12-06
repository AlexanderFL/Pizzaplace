#pragma once

#include "Data.h"
#include "InvalidLogin.h"

class LoginService
{
private:
	Data repo;
public:
	LoginService();
	int login(string username, string password);
};

