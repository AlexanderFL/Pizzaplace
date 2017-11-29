#ifndef MAINUI_H
#define MAINUI_H

//#include "Pizza.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> //tolower case string in MainUI cpp ( start ui)

using namespace std;

class MainUI
{
    private:

    public:
        MainUI();
        virtual ~MainUI();
        void startUI();
};

#endif // MAINUI_H
