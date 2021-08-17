module;
#if USE_ZLOG_MODULE
#  include "zlog/marco.h"
#else
#  include <iostream>
#  include <vector>
#  include <zlog.hpp>
#endif
module main;

#if USE_ZLOG_MODULE
import std.core;
import zlog;
#endif

int main()
{
    ZDBG("hello");
    int i = 100;
    ZDBG(i);
    ZDBG(true);
    ZDBG(std::string("str"));
    std::vector<int> vec{ 1,2,3 };
    ZDBG(vec);
    //int a[3];
    //a[0] = 1;
    //a[1] = 2;
    //a[2] = 3;
    //ZDBG(a);
    return 0;
}
