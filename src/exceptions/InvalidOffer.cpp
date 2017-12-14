#include "InvalidOffer.h"


InvalidOffer::InvalidOffer(const string& message)
{
	this->message = message;
}

string InvalidOffer::getMessage() {
	return this->message;
}