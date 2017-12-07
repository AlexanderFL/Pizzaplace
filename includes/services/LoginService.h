#pragma once

#include "Data.h"
#include "User.h"
#include "InvalidLogin.h"

class LoginService
{
private:
	Data repo;
public:
	LoginService();
	profession login(string username, string password);
};

