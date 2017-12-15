#pragma once

#include "CommonService.h"
#include "NumberInString.h"
#include "InvalidPrice.h"
#include "Offer.h"
#include "EmptyVector.h"
#include "NumberInString.h"
#include "InvalidString.h"
#include "InvalidInt.h"
#include "InvalidOffer.h"

class ManagerService: public CommonService
{
private:
	Data repo;
public:
	ManagerService();
	void replaceToppingInFile(const Topping& topping, int index);

	//Validation
	void containsOnlyAlpha(string s);
	void validPrice(int p);
	void validProcent(int p);
	void validateOffer(const Offer& offer);
};