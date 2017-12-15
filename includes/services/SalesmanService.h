#pragma once

#include "CommonService.h"
#include "InvalidOrder.h"
#include "InvalidAddress.h"
#include "InvalidInput.h"

class SalesmanService : public CommonService
{
private:
    Data _repo;
    Pizza _pizza;
    SideOrder _sides;
public:
    SalesmanService();
    // Editing orders
    void registerNewOrder(Order &order);
    void appendToOrder(Order &firstOrder, Order &secondOrder);
    void appendToOrder(Order &firstOrder, Pizza &pizza);
    void appendToOrder(Order &order, SideOrder &sideAppend);
    int getPriceOfOrder(Order &order);
    int getOldPriceOfOrder(Order &order);
    void assignHomeAddress(Order &order, string address);
    void setOrderToDelivery(Order &order);
    void setOrderToPickUp(Order &order);
    void setOrderAsPaid(Order &order);
    void setComments(Order &order, string comment);
    bool validateOrder(Order order);
    void validInput(const string &input, const int &max, const int &min = 1) const;
    SideOrder getSideOrder();
    Pizza getPizza();
    //Gets all of the offer names that the order consists of
    vector<string> getOfferNames(const Order &order);
    //Gets name of the pizza
    string getSingleOfferName(const Pizza &pizza);
    //Calculates the cost of a pizza
    int calculateCost(const Pizza &pizza);
private:
    //Calculates the cost of a order
    int calculateCost(const Order &order);
    int calculateOldCost(const Order &order);
    //Calculates the cost of a pizza as is without looking at offers
    int calculateSimpleCost(const Pizza &pizza);
    int calculateOldCost(const Pizza &pizza);
    void overrideOrder(int index, Order edit);
    //Assigns an ID to the order and all of the pizzas within it
    void assignID(Order &order);
    //Gets all offers that consist of a single pizza
    vector<Offer> getSinglePizzaOffers();
    //Gets all offers that don't consist of a single pizza
    vector<Offer> getCompOffers();
    //Returns how similar two orders are to eachother
    double orderSimularity(const Order &left, const Order &right);
    //Returns how similar two pizzas are to eachother
    double pizzaSimularity(const Pizza &left, const Pizza &right);
};