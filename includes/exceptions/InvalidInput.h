#pragma once
#include <string>
class InvalidInput
{
private:
	std::string _message;
public:
	InvalidInput();
	explicit InvalidInput(const std::string& message);

	std::string getMessage();
};
