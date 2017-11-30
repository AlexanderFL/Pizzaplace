#ifndef TOPPINGREPOSITORY_H
#define TOPPINGREPOSITORY_H

#include "Topping.h"

class ToppingRepository {
    private:
        string file;
    public:
        ToppingRepository();
        void storeTopping(const Topping& topping) const;
        Topping retrieveTopping() const;
};


#endif //TOPPINGREPOSITORY_H
