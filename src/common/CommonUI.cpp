#include "CommonUI.h"
#include <iomanip> //setw
#include <stdlib.h>

void
CommonUI::clear() const
{
	system("CLS");
}

void
CommonUI::printMenu(const vector<string> &options) const
{
	printOptions(options, biggestStringSize(options));
}

void
CommonUI::printMenu(const vector<string> &options, const string &title, const bool &displayOnly) const
{
	vector<string> temp = options;
	temp.push_back(title);
	size_t biggest = biggestStringSize(temp);
	printLines(biggest);
	cout << "\t| " << title;
	for (size_t j = 0; j < ((biggest * 2) - title.size()); j++)
	{
		cout << " ";
	}
	cout << "          |\n";
	printOptions(options, biggest, displayOnly);
}

void
CommonUI::printArrow(const string &str) const
{
	cout << "\t|\n\t-->" << str << ": ";
}

void
CommonUI::printMessage(const string &str) const
{
	cout << "\t";
	for (unsigned int i = 0; i < str.size() + 4; i++)
	{
		cout << "-";
	}
	cout << "\n\t| " << str << " |\n\t";
	for (unsigned int i = 0; i < str.size() + 4; i++)
	{
		cout << "-";
	}
	cout << endl;
}

void
CommonUI::getInput(string &str) const
{
	printArrow("Input");
	cin >> ws;
	getline(cin, str);
}

void
CommonUI::getInput(const string &text, string &str) const
{
	printArrow(text);
	cin >> ws;
	getline(cin, str);
}

void
CommonUI::getInput(const string &text, char &input) const
{
	printArrow(text);
	input = _getwche();
	cout << endl;
}

//Private functions

//print out minus signs (for lines)
void
CommonUI::printLines(size_t size) const
{
	cout << "\t";
	for (unsigned int i = 0; i < size * 2; i++)
	{
		cout << "-";
	}
	cout << "-------------\n";
}

void
CommonUI::printOptions(const vector<string> &options, size_t biggest, bool displayOnly) const
{
	for (size_t i = 0; i < options.size(); i++)
	{
		printLines(biggest);
		cout << "\t| " << i + 1 << ".";
		if (i + 1 < 10)
		{
			cout << " ";
		}
		cout << options.at(i);
		/*if (!displayOnly) {
		cout << "\t| " << i + 1 << ". " << options.at(i);
		}
		else {
		cout << "\t| " << options.at(i);
		}*/
		for (size_t j = 0; j < (biggest - options.at(i).size()); j++)
		{
			cout << " ";
		}
		cout << " | ";
		i++;

		//if there is an odd number of options, then the last box needs to be empty
		if (options.size() == i)
		{
			cout << "   ";
			for (size_t j = 0; j < biggest; j++)
			{
				cout << " ";
			}
			if (displayOnly)
			{
				cout << "   ";
			}
		}
		else
		{
			cout << i + 1 << ".";
			if (i + 1 < 10)
			{
				cout << " ";
			}
			cout << options.at(i);
			/*if (!displayOnly) {
			cout << i + 1 << ". " << options.at(i);
			}
			else {
			cout << options.at(i) << "\t   ";
			}*/
			for (size_t j = 0; j < (biggest - options.at(i).size()); j++)
			{
				cout << " ";
			}
		}
		cout << " |\n";
	}
	printLines(biggest);
}

size_t
CommonUI::biggestStringSize(const vector<string> &vec) const
{
	size_t biggest = 0;
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (biggest < vec.at(i).size())
		{
			biggest = vec.at(i).size();
		}
	}
	return biggest;
}

//Printing the order
void
CommonUI::showPizzaInfoShort(const Pizza &pizza) const
{
	cout << pizza.getToppings().size() << " toppings, ";
	cout << pizza.getPizzaSize().getName() << " ";
	cout << pizza.getCrust().getName() << " pizza.";
}

void
CommonUI::showOrderInfo(const Order &order) const
{
	//TODO: FIX
	cout << "\n\t\tPizza Place " << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "Order ID: " << order.getID() << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "Pizza:\t\t\t";
	if (order.getPizzas().size() == 0)
	{
		cout << "None";
	}
	else
	{
		for (size_t i = 0; i < order.getPizzas().size(); ++i)
		{
			showPizzaInfoShort(order.getPizzas().at(i));
		}

	}
	cout << endl << "Side Orders:\t\t";
	if (order.getSides().size() == 0)
	{
		cout << "None";
	}
	else
	{
		for (size_t i = 0; i < order.getSides().size(); ++i)
		{
			cout << order.getSides().at(i).getName();
		}
	}
	cout << endl << "Comment:\t\t" + order.getComment() << endl;
	cout << "Location:\t\t" + order.getLocation().getAddress() << endl;
	cout << "Delivery Method:\t";
	if (order.getDeliveryMethod() == PICKUP)
	{
		cout << "Pickup" << endl;
	}
	else if (order.getDeliveryMethod() == SEND)
	{
		cout << "Send to " << order.getHomeAddress() << endl;
	}
	cout << "Paid:\t\t\t";
	if (order.isPaidFor())
	{
		cout << "True";
	}
	else
	{
		cout << "False" << endl;
	}
	cout << endl;
}

void
CommonUI::showOrderInfoShort(const Order &order) const
{
	cout << order.getPizzas().size() << " pizzas, ";
	cout << order.getSides().size() << " side orders, ";
	if (order.isPaidFor())
	{
		cout << "paid, ";
	}
	else
	{
		cout << "unpaid, ";
	}
	if (order.getDeliveryMethod() == SEND)
	{
		cout << "needs to be sent";
	}
	else
	{
		cout << "awaiting pickup";
	}
	cout << endl;
}