#pragma once

#include "Menu.h"
#include "LoginService.h"

class LoginUI
{
private:
	Menu menu;
	LoginService service;
public:
	void startUI();
};

