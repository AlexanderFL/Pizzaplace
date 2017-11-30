#ifndef TESTREPO_H
#define TESTREPO_H

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


#endif //TESTREPO_H
