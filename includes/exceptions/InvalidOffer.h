#pragma once

#include <string>

using namespace std;

class InvalidOffer
{
private:
	string message;
public:
	InvalidOffer(const string& message);
	string getMessage();
};

