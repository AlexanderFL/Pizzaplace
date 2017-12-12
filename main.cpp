#include <iostream>

#include "Data.h"
#include <type_traits>

#include "SalesmanService.h"

#include "MainUI.h"
//#include <cstdlib>
//#include <time.h>
#define DEFINE_MEMBER_CHECKER(member) \
    template<typename T, typename V = bool> \
    struct has_ ## member : false_type { }; \
    template<typename T> \
    struct has_ ## member<T, \
        typename enable_if< \
            !is_same<decltype(declval<T>().member), void>::value, \
            bool \
            >::type \
        > : true_type { };

#define HAS_MEMBER(C, member) \
    has_ ## member<C>::value

using namespace std;

Data repo;

int main()
{
	MainUI mainUI;
	mainUI.startUI();

	return 0;
}