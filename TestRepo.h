//
// Created by Thomas Ari Bech on 29.11.17.
//

#ifndef PIZZAPLACE_TESTREPO_H
#define PIZZAPLACE_TESTREPO_H

#include <vector>
#include "Test.h"

class TestRepo {
    private:
        string file;
    public:
        TestRepo();
        void storeTest(const vector<Test>& test) const;
        vector<Test> retrieveTest() const;
};


#endif //PIZZAPLACE_TESTREPO_H
