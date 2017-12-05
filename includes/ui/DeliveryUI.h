#include <iostream>
#include <string>
using namespace std;

class DeliveryUI
{
	bool ignore;
public:
	DeliveryUI();
	~DeliveryUI();
	void setIgnore(bool ignore);
	void deliveryMenu();
};

