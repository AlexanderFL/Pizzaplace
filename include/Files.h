#ifndef FILES_H
#define FILES_H

#include <iostream>
#include <fstream>
#include <string>
#include "Pizza.h"

using namespace std;

/// This class is for using file streams
/// to read and write files
class Files
{
private:
    string orders;
    string finishedOrders;
    string menu;
public:
    Files();

    bool AddOrder(Pizza pizza);
};

#endif // FILES_H
