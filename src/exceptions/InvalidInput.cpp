#include "InvalidInput.h"


InvalidInput::InvalidInput()
{
}

InvalidInput::InvalidInput(const std::string& message)
	:_message(message)
{
}


std::string InvalidInput::getMessage() const
{
	return _message;
}