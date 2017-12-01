#ifndef TOPPINGREPOSITORY_H
#define TOPPINGREPOSITORY_H

#include <vector>
#include "Topping.h"

class ToppingRepository {
    private:
        string file;
    public:
        ToppingRepository();
        void storeToppings(const vector<Topping>& toppings) const;
        vector<Topping> retrieveToppings() const;
		void storeTopping(const Topping& topping) const;
		Topping retrieveTopping(int& loc) const;
};


#endif //TOPPINGREPOSITORY_H
