#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Pizza.h"
#include "SideOrder.h"
#include "Location.h"
using namespace std;

/*
	Keeps the user order, which can be multiple pizzas 
	and allows the user to edit his order.
*/

enum deliveryMethod { PICKUP = 0, SEND };

class Order
{
public:
    static const string filename;
private:
    vector<Pizza> pizzas;
    vector<SideOrder> sides;
    status _status;
    Location location;
    string comment;
    string homeAddress;
    deliveryMethod _deliveryMethod;
    bool paidFor;
    size_t id;
public:
    /*	Constructors	*/
    Order();
    Order(vector<Pizza> pizzas,
          vector<SideOrder> sides,
          status orderStatus,
          Location location,
          string comment,
          string homeAddress,
          deliveryMethod orderDeliveryMethod,
          bool isPaid);

    /*	Get Functions	*/
    //Gets all the pizzas
    vector<Pizza>
    getPizzas() const;
    //Gets all the side orders
    vector<SideOrder>
    getSides() const;
    //Gets the status
    status
    getStatus() const;
    //Gets the location
    Location
    getLocation() const;
    //Gets the comment
    string
    getComment() const;
    //Gets the home address
    string
    getHomeAddress() const;
    //Gets the delivery method
    deliveryMethod
    getDeliveryMethod() const;
    //Returs true if it is paid otherwise false
    bool
    isPaidFor() const;
    //Gets the ID
    size_t
    getID() const;

    /* 	Set Functions	*/
    //Sets the pizzas
    void
    setPizzas(const vector<Pizza> &pizzas);
    //Sets the side orders
    void
    setSides(const vector<SideOrder> &sides);
    //Sets the status
    void
    setStatus(const status &orderStatus);
    //Sets the location
    void
    setLocation(const Location &location);
    //Sets the comments
    void
    setComment(const string &comment);
    //Sets the home address
    void
    setHomeAddress(const string &homeAddress);
    //Sets the delivery method
    void
    setDeliveryMethod(const deliveryMethod &orderDeliveryMethod);
    //Sets it as paid or not
    void
    setOrderAsPaidFor(bool isPaid);
    //Sets the ID
    void
    setID(const size_t &id);

    /*	Operator overloads	*/
    friend ostream &
    operator<<(ostream &out, const Order &order);
    friend istream &
    operator>>(istream &in, Order &order);
    friend bool
    operator==(const Order &left, const Order &right);
    friend bool
    operator!=(const Order &left, const Order &right);
    friend bool
    operator<=(const Order &left, const Order &right);
    friend Order
    operator*(const Order &left, const Order &right);
    friend Order
    operator+(const Order &left, const Order &right);
    friend Order
    operator-(const Order &left, const Order &right);
};
