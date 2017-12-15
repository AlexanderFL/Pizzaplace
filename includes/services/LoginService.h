#pragma once

#include "CommonService.h"
#include "User.h"
#include "InvalidLogin.h"
#include "EmptyVector.h"

class LoginService : public CommonService
{
private:
    Data repo;
public:
    LoginService();
    //Validates if the login info is valid
    profession login(string username, string password);
    //Checks if there exists any users
    void checkForUsers();
};

