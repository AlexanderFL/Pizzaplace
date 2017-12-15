#pragma once

#include "CommonUI.h"
#include "LoginService.h"

/*NOT IN USE*/
class LoginUI : public CommonUI
{
private:
	LoginService service;
public:
	void startUI();
};

