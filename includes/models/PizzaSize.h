#pragma once

#include <iostream>
#include <string>

using namespace std;

class PizzaSize
{
public:
    static const string filename;
private:
    string name;
    double pricemod;
public:
    /*	Constructors	*/
    PizzaSize();
    PizzaSize(const string &name, double pricemod);

    /*	Get Functions	*/
    //Gets the name
    string getName() const;
    //Gets the price modifier
    double getPriceMod() const;

    /*	Set Functions	*/
    //Sets the name
    void setName(const string &name);
    //Sets the price modifier
    void setPriceMod(const double &pricemod);

    /*	Operator Overloads	*/
    friend ostream &operator<<(ostream &out, const PizzaSize &size);
    friend istream &operator>>(istream &in, PizzaSize &size);
    friend bool operator==(const PizzaSize &left, const PizzaSize &right);
};

