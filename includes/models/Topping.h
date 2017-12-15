#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Topping
{
public:
    static const string filename;
private:
    string name;
    int price;
public:
    /*	Constructors	*/
    Topping();
    Topping(string name, int price);

    /*	Get Functions	*/
    //Gets the name
    string getName() const;
    //Gets the price
    int getPrice() const;

    /*	Set Functions	*/
    //Sets the name
    void setName(const string &name);
    //Sets the price
    void setPrice(const int &price);

    /*	Operator Overloads	*/
    friend istream &operator>>(istream &in, Topping &topping);
    friend ostream &operator<<(ostream &out, const Topping &topping);
    friend bool operator==(const Topping &left, const Topping &right);
};
