#pragma once

#include "CommonService.h"
#include "User.h"
#include "InvalidLogin.h"
#include "EmptyVector.h"

class LoginService: public CommonService
{
private:
	Data repo;
public:
	LoginService();
	profession login(string username, string password);
	void checkForUsers();
};

