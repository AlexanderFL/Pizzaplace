#include "CommonService.h"

void CommonService::validateStringIsDigit(const string& str) const {
	if (str.length() == 0) {
		throw InvalidString();
	}
	size_t i = 0;
	if (str[0] == '-') {
		++i;
	}
	for (i; i < str.length(); ++i) {
		if (!isdigit(str[i])) {
			throw InvalidString();
		}
	}
}

int CommonService::convertStringToInt(const string& str) const {
	validateStringIsDigit(str);
	return stoi(str);
}