#include <fstream>
#include "Order.h"

/*
*************************************************
				PUBLIC FUNCTIONS
*************************************************
*/

Order::Order() 
{ 
	totalCost = 0;
	comment = "";
	status = 0;
	location = 0;
	homeAddress = "none";

}

/*
	Prompt the user for his order, the user can select multiple pizzas and
	can change his order or cancel his order.

	TODO: Complete the Pizza class for istream input and input options UI
*/

void Order::MakeOrder()
{
	Pizza tempPizza;
	//Maybe skip the comment "New Order". Commented it out at least for now
	//cout << "New Order" << endl;
	cin >> tempPizza; // TODO: Finish this.
}

/*
	Writes the user order to a binary file after the user has completed his order
*/
void Order::write(ofstream& fout) const {
	int size = pizzas.size();
	fout.write((char*)(&size), sizeof(int));
	for (int i = 0; i < size; ++i) {
		pizzas.at(i).write(fout);
	}
	size = sides.size();
	fout.write((char*)(&size), sizeof(int));
	for (int i = 0; i < size; ++i) {
		sides.at(i).write(fout);
	}
	fout.write((char*)(&totalCost), sizeof(double));
	fout.write((char*)(&status), sizeof(int));
	fout.write((char*)(&location), sizeof(int));
	int len = comment.length() + 1;
	fout.write((char*)(&len), sizeof(int));
	fout.write(comment.c_str(), len);
}

/*
	Reads the user order from a binary file, which can be read from the kitchen
*/
void Order::read(ifstream& fin) {
	pizzas.clear();
	sides.clear();
	int size;
	Pizza pizza;
	fin.read((char*)(&size), sizeof(int));
	for (int i = 0; i < size; ++i) {
		pizza.read(fin);
		pizzas.push_back(pizza);
	}
	fin.read((char*)(&size), sizeof(int));
	SideOrder side;
	for (int i = 0; i < size; ++i) {
		side.read(fin);
		sides.push_back(side);
	}
	fin.read((char*)(&totalCost), sizeof(double));
	fin.read((char*)(&status), sizeof(int));
	fin.read((char*)(&location), sizeof(int));
	int len;
	fin.read((char*)(&len), sizeof(int));
	char* str = new char[len];
	fin.read(str, len);
	comment = str;
	delete[] str;
}

/*
	Get total cost for the order
*/
double Order::getTotalCost() {
	calculateCost();
	return totalCost;
}

/*
*************************************************
				PRIVATE FUNCTIONS
*************************************************
*/

/*
	Calculates the total cost for the order,
	Based on how many pizzas were ordered, size of them and what toppings.
*/
void Order::calculateCost() {
	totalCost = 0;
	for (unsigned int i = 0; i < pizzas.size(); ++i) {
		totalCost += pizzas.at(i).getCost();
	}
	for (unsigned int i = 0; i < sides.size(); ++i) {
		totalCost += sides.at(i).getPrice();
	}
}

//To get the home address of a person (TODO: fix)
void Order::setHomeAddress(string address) {
	homeAddress = address;
}

string Order::getHomeAddress() {
	return homeAddress;
}
/*
*************************************************
				OVERLOAD FUNCTIONS
*************************************************
*/

/*
	Prints the order from a user.
*/
ostream& operator <<(ostream& out, const Order& order)
{
	out << "order";
	return out;
}

bool operator == (const Order& left, const Order& right) {
	if (left.pizzas.size() != right.pizzas.size() || left.sides.size() != right.sides.size()) {
		return false;
	}
	for (int i = 0; i < left.pizzas.size(); ++i) {
		
	}
	return true;
}

