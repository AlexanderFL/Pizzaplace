#pragma once

#include "CommonUI.h"
#include "LoginService.h"

class LoginUI: public CommonUI
{
private:
	LoginService service;
public:
	void startUI();
};

