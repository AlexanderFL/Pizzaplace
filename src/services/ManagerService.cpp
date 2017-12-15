#include "ManagerService.h"

ManagerService::ManagerService() {}

void ManagerService::replaceToppingInFile(const Topping &topping, int index)
{
	vector<Topping> toppings = repo.RetrieveAllFromFile<Topping>();
	toppings[index] = topping;
	repo.WriteMultipleLinesToFile<Topping>(toppings);
}

/*		Checks if string contains only alpha characters
Returns true if it does and false otherwise.

Examples for usage: If topping contains a number,
the function will return false,
because it is not a valid topping name.
*/
void ManagerService::containsOnlyAlpha(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (!isalpha(s[i]))
		{
			throw NumberInString();
		}
	}
}

/*
Checks if price is valid, a price is valid if it is
not a number below zero.
*/

void ManagerService::validPrice(int p)
{
	if (p <= 0)
	{
		throw InvalidPrice();
	}
}

void ManagerService::validProcent(int p)
{
	if (p <= 0 || p >= 100)
	{
		throw InvalidPrice();
	}
}

void ManagerService::validateOffer(const Offer &offer)
{
	if (offer.getOrder().getPizzas().empty() && offer.getOrder().getSides().empty())
	{
		throw InvalidOffer("Offer needs to have a pizza or side in it.");
	}
	if (offer.getPrice() == 0)
	{
		throw InvalidOffer("Price needs to be set.");
	}
	if (offer.getName() == "Unnamed")
	{
		throw InvalidOffer("Offer can't be Unnamed");
	}
}