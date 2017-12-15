#include "KitchenUI.h"

KitchenUI::KitchenUI() {}

void KitchenUI::showMainMenu()
{
	string input;
	while (true)
	{
		try
		{
			vector<Location> locations = service.getItems<Location>();
			vector<string> names;
			for (size_t i = 0; i < locations.size(); ++i)
			{
				names.push_back(locations.at(i).getAddress());
			}
			names.push_back("Back");
			printMenu(names, "Select Location");
			try
			{
				getInput(input);
				int index = service.convertStringToInt(input);
				int place = index - 1;
				if (index == names.size())
				{
					clear();
					return;
				}
				vector<Pizza> pizzas = service.getPizzas(locations.at(place));
				clear();
				while (true)
				{
					names.clear();
					for (size_t i = 0; i < pizzas.size(); ++i)
					{
						names.push_back("Pizza " + to_string(pizzas.at(i).getID()));
					}
					names.push_back("Back");
					printMenu(names, "Incomplete Pizzas");
					getInput(input);
					try
					{
						index = service.convertStringToInt(input);
						if (index == names.size())
						{
							clear();
							break;
						}
						clear();
						while (true)
						{
							printMessage(showPizzaInfo(pizzas.at(index - 1)));
							if (pizzas.at(index - 1).getPhase() == PREPERATION)
							{
								printMenu({ "Set as Baking", "Back" }, "Select option");
								getInput(input);
								if (input == "1")
								{
									clear();
									service.setPizzaAsBaking(pizzas.at(index - 1).getID());
									pizzas = service.getPizzas(locations.at(place));
									printMessage("Pizza set to baking.");
								}
								else if (input == "2")
								{
									clear();
									break;
								}
								else
								{
									clear();
									printMessage("Invalid input.");
								}
							}
							else
							{
								printMenu({ "Set as Ready", "Back" }, "Select option");
								getInput(input);
								if (input == "1")
								{
									clear();
									service.setPizzaAsReady(pizzas.at(index - 1).getID());
									pizzas = service.getPizzas(locations.at(place));
									printMessage("Pizza set to ready.");
									break;
								}
								else if (input == "2")
								{
									clear();
									break;
								}
								else
								{
									clear();
									printMessage("Invalid input.");
								}
							}
						}
					}
					catch (out_of_range)
					{
						clear();
						printMessage("Invalid index.");
					}
				}
			}
			catch (InvalidString)
			{
				clear();
				printMessage("Invalid input.");
			}
			catch (out_of_range)
			{
				clear();
				printMessage("Invalid index.");
			}
			catch (EmptyVector)
			{
				clear();
				printMessage("No pizzas available for this location.");
			}
			catch (FailedOpenFile)
			{
				clear();
				printMessage("Failed to open file.");
			}
		}
		catch (EmptyVector)
		{
			clear();
			printMessage("No locations available.");
			break;
		}
		catch (FailedOpenFile)
		{
			clear();
			printMessage("Failed to open file.");
			return;
		}
	}
}

string KitchenUI::showPizzaInfo(const Pizza &pizza) const
{
	string info = "A ";
	info += pizza.getPizzaSize().getName() + " pizza with ";
	if (pizza.getToppings().size() == 0)
	{
		info += "no toppings, ";
	}
	else
	{
		for (size_t i = 0; i < pizza.getToppings().size(); ++i)
		{
			info += pizza.getToppings().at(i).getName() + ", ";
		}
	}
	info += pizza.getCrust().getName() + " crust.";
	info += " It is currently";
	if (pizza.getPhase() == PREPERATION)
	{
		info += " in preperation.";
	}
	else if (pizza.getPhase() == BAKING)
	{
		info += " baking.";
	}
	return info;
}