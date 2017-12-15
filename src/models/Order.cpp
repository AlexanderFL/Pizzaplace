#include <fstream>
#include "Order.h"

/*
*************************************************
				PUBLIC FUNCTIONS
*************************************************
*/

const string Order::filename = "orders.dat";

Order::Order()
{
    comment = "";
    _status = PREPERATION;
    location = Location("None");
    homeAddress = "none";
    _deliveryMethod = PICKUP;
    paidFor = false;
}

Order::Order(vector<Pizza> pizzas,
             vector<SideOrder> sides,
             status orderStatus,
             Location location,
             string comment,
             string homeAddress,
             deliveryMethod orderDeliveryMethod,
             bool isPaid)
{
    this->pizzas = pizzas;
    this->sides = sides;
    this->_status = orderStatus;
    this->sides = sides;
    this->_status = orderStatus;
    this->location = location;
    this->comment = comment;
    this->homeAddress = homeAddress;
    this->_deliveryMethod = orderDeliveryMethod;
    this->paidFor = isPaid;
}

vector<Pizza>
Order::getPizzas() const
{
    return this->pizzas;
}

vector<SideOrder>
Order::getSides() const
{
    return this->sides;
}

status
Order::getStatus() const
{
    return this->_status;
}

Location
Order::getLocation() const
{
    return this->location;
}

string
Order::getComment() const
{
    return this->comment;
}

string
Order::getHomeAddress() const
{
    return this->homeAddress;
}

deliveryMethod
Order::getDeliveryMethod() const
{
    return _deliveryMethod;
}

bool
Order::isPaidFor() const
{
    return paidFor;
}

size_t
Order::getID() const
{
    return this->id;
}

void
Order::setPizzas(const vector<Pizza> &pizzas)
{
    this->pizzas = pizzas;
}

void
Order::setSides(const vector<SideOrder> &sides)
{
    this->sides = sides;
}

void
Order::setStatus(const status &orderStatus)
{
    this->_status = orderStatus;
}

void
Order::setLocation(const Location &location)
{
    this->location = location;
}

void
Order::setComment(const string &comment)
{
    this->comment = comment;
}

void
Order::setHomeAddress(const string &homeAddress)
{
    this->homeAddress = homeAddress;
}

void
Order::setDeliveryMethod(const deliveryMethod &orderDeliveryMethod)
{
    this->_deliveryMethod = orderDeliveryMethod;
}

void
Order::setOrderAsPaidFor(bool isPaid)
{
    this->paidFor = isPaid;
}

void
Order::setID(const size_t &id)
{
    this->id = id;
}

/*
*************************************************
				PRIVATE FUNCTIONS
*************************************************
*/


/*
*************************************************
				OVERLOAD FUNCTIONS
*************************************************
*/

/*
	Prints the order from a user.
*/
ostream &
operator<<(ostream &out, const Order &order)
{
    if (&out != &cout)
    {
        size_t size = order.pizzas.size();
        out.write((char *) (&size), sizeof(size_t));
        for (size_t i = 0; i < size; ++i)
        {
            out << order.pizzas.at(i);
        }
        size = order.sides.size();
        out.write((char *) (&size), sizeof(size_t));
        for (size_t i = 0; i < size; ++i)
        {
            out << order.sides.at(i);
        }
        out.write((char *) (&order._status), sizeof(status));
        out << order.location;
        size_t len = order.comment.length() + 1;
        out.write((char *) (&len), sizeof(size_t));
        out.write(order.comment.c_str(), len);
        len = order.homeAddress.length() + 1;
        out.write((char *) (&len), sizeof(size_t));
        out.write(order.homeAddress.c_str(), len);
        out.write((char *) (&order.paidFor), sizeof(bool));
        out.write((char *) (&order._deliveryMethod), sizeof(deliveryMethod));
        out.write((char *) (&order.id), sizeof(size_t));
    }
    else
    {
        // This was for debugging purposes only
        // Feel free to change it, it won't (shouldn't)
        // break anything, if it does, contact god. -A
        for (int i = 0; i < order.pizzas.size(); i++)
        {
            out << "Pizza " << i << ": " << order.pizzas[i] << endl;
        }
    }
    return out;
}

istream &
operator>>(istream &in, Order &order)
{
    if (&in != &cin)
    {
        order.pizzas.clear();
        order.sides.clear();
        size_t size;
        Pizza pizza;
        in.read((char *) (&size), sizeof(size_t));
        for (size_t i = 0; i < size; ++i)
        {
            in >> pizza;
            order.pizzas.push_back(pizza);
        }
        in.read((char *) (&size), sizeof(size_t));
        SideOrder side;
        for (size_t i = 0; i < size; ++i)
        {
            in >> side;
            order.sides.push_back(side);
        }
        in.read((char *) (&order._status), sizeof(status));
        in >> order.location;
        size_t len;
        in.read((char *) (&len), sizeof(size_t));
        char *str = new char[len];
        in.read(str, len);
        order.comment = str;
        delete[] str;
        in.read((char *) (&len), sizeof(size_t));
        str = new char[len];
        in.read(str, len);
        order.homeAddress = str;
        delete[] str;
        in.read((char *) (&order.paidFor), sizeof(bool));
        in.read((char *) (&order._deliveryMethod), sizeof(deliveryMethod));
        in.read((char *) (&order.id), sizeof(size_t));
    }
    return in;
}

bool
operator==(const Order &left, const Order &right)
{
    Order order = left * right;
    return left.pizzas.size() == order.pizzas.size() && left.sides.size() == order.sides.size()
        && right.pizzas.size() == order.pizzas.size() && right.sides.size() == right.sides.size();
}

bool
operator!=(const Order &left, const Order &right)
{
    return !(left == right);
}

bool
operator<=(const Order &left, const Order &right)
{
    Order order = left * right;
    return left == order;
}

Order
operator*(const Order &left, const Order &right)
{
    Order order;
    for (int i = 0; i < left.pizzas.size(); ++i)
    {
        for (int j = 0; j < right.pizzas.size(); ++j)
        {
            if (left.pizzas.at(i) == right.pizzas.at(j))
            {
                order.pizzas.push_back(left.pizzas.at(i));
                break;
            }
        }
    }
    for (int i = 0; i < left.sides.size(); ++i)
    {
        for (int j = 0; j < right.sides.size(); ++j)
        {
            if (left.sides.at(i) == right.sides.at(j))
            {
                order.sides.push_back(left.sides.at(i));
                break;
            }
        }
    }
    return order;
}

// The + operator ONLY adds together the vectors pizzas and sides
Order
operator+(const Order &left, const Order &right)
{
    Order newOrder;
    // Copy left Order into newOrder
    newOrder = left;

    // Append right pizzas together into newOrder
    for (int i = 0; i < right.pizzas.size(); i++)
    {
        newOrder.pizzas.push_back(right.pizzas[i]);
    }

    // Append right side orders into newOrder
    for (int i = 0; i < left.sides.size(); i++)
    {
        newOrder.sides.push_back(left.sides[i]);
    }

    return newOrder;
}

Order
operator-(const Order &left, const Order &right)
{
    Order newOrder = left;
    Order temp = right;
    while (temp.pizzas.size() > 0)
    {
        for (size_t i = 0; i < newOrder.pizzas.size(); ++i)
        {
            if (newOrder.pizzas.at(i) == temp.pizzas.at(0))
            {
                newOrder.pizzas.erase(newOrder.pizzas.begin() + i);
                temp.pizzas.erase(temp.pizzas.begin());
                break;
            }
        }
    }
    while (temp.sides.size() > 0)
    {
        for (size_t i = 0; i < newOrder.sides.size(); ++i)
        {
            if (newOrder.sides.at(i) == temp.sides.at(0))
            {
                newOrder.sides.erase(newOrder.sides.begin() + i);
                temp.sides.erase(temp.sides.begin());
                break;
            }
        }
    }
    return newOrder;
}