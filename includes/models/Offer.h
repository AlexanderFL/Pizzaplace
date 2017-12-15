#pragma once
#include <iostream>
#include <string>
#include "Order.h"

using namespace std;

class Offer
{
public:
    static const string filename;
private:
    string name;
    Order order;
    int price;
public:
    /*	Constructor	 */
    Offer();
    Offer(string name, Order order, int price);

    /*	Get Functions	*/
    //Gets the name
    string
    getName() const;
    //Gets the order
    Order
    getOrder() const;
    //Gets the price
    int
    getPrice() const;

    /*	Set Functions	*/
    //Sets the name
    void
    setName(const string &name);
    //Sets the order
    void
    setOrder(const Order &order);
    //Sets the price
    void
    setPrice(const int &price);

    /*	Operator Overloads	*/
    friend ostream &
    operator<<(ostream &out, const Offer &offer);
    friend istream &
    operator>>(istream &in, Offer &offer);
};
