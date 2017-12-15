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
	//Replaces the topping in the file at the index
	void replaceToppingInFile(const Topping& topping, int index);

	//Validation
	//Checks if the string only contains alpha characters
	void containsOnlyAlpha(string s);
	//Checks if the price is aboce 0
	void validPrice(int p);
	//Checks if the int is above 0 or below 100
	void validProcent(int p);
	//Validates that the offer isn't emppty and has a price and name set
	void validateOffer(const Offer& offer);
};