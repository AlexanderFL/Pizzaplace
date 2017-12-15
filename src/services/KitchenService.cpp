#include "KitchenService.h"

KitchenService::KitchenService() {}

void
KitchenService::setPizzaAsBaking(const size_t &id)
{
    vector<Order> orders = getItems<Order>();
    for (size_t i = 0; i < orders.size(); ++i)
    {
        for (size_t j = 0; j < orders.at(i).getPizzas().size(); ++j)
        {
            if (orders.at(i).getPizzas().at(j).getID() == id)
            {
                vector<Pizza> pizzas = orders.at(i).getPizzas();
                pizzas.at(j).setPhase(BAKING);
                orders.at(i).setPizzas(pizzas);
                repo.WriteMultipleLinesToFile(orders);
                return;
            }
        }
    }
}

void
KitchenService::setPizzaAsReady(const size_t &id)
{
    vector<Order> orders = getItems<Order>();
    for (size_t i = 0; i < orders.size(); ++i)
    {
        for (size_t j = 0; j < orders.at(i).getPizzas().size(); ++j)
        {
            if (orders.at(i).getPizzas().at(j).getID() == id)
            {
                vector<Pizza> pizzas = orders.at(i).getPizzas();
                pizzas.at(j).setPhase(READY);
                int counter = 0;
                for (size_t k = 0; k < pizzas.size(); ++k)
                {
                    if (pizzas.at(k).getPhase() == READY)
                    {
                        ++counter;
                    }
                }
                if (orders.at(i).getPizzas().size() == counter)
                {
                    orders.at(i).setStatus(READY);
                }
                orders.at(i).setPizzas(pizzas);
                repo.WriteMultipleLinesToFile(orders);
                return;
            }
        }
    }
}

vector<Pizza>
KitchenService::getPizzas(const Location &location)
{
    vector<Pizza> pizzas;
    vector<Order> orders = getItems<Order>();
    for (size_t i = 0; i < orders.size(); ++i)
    {
        if (orders.at(i).getLocation() == location && orders.at(i).getStatus() == PREPERATION)
        {
            for (size_t j = 0; j < orders.at(i).getPizzas().size(); ++j)
            {
                if (orders.at(i).getPizzas().at(j).getPhase() == PREPERATION
                    || orders.at(i).getPizzas().at(j).getPhase() == BAKING)
                {
                    pizzas.push_back(orders.at(i).getPizzas().at(j));
                }
            }
        }
    }
    validateVectorNotEmpty(pizzas);
    return pizzas;
}