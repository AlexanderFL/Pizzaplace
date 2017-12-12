#ifndef MAINUI_H
#define MAINUI_H

//#include "Pizza.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> //tolower case string in MainUI cpp (start ui)
#include <vector>
#include "CommonUI.h"

using namespace std;

class MainUI: public CommonUI
{
    public:
        void startUI();
};

#endif // MAINUI_H
