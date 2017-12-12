#pragma once

#include "CommonUI.h"
#include "LoginService.h"

class LoginUI: CommonUI
{
private:
	LoginService service;
public:
	void startUI();
};

