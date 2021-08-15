#include <iostream>
#include <vector>
#include <zlog.hpp>

int main()
{
    ZDBG("hello");
    int i = 100;
    ZDBG(i);
    ZDBG(std::string("str"));
    std::vector<int> vec{ 1,2,3 };
    ZDBG(vec);
    return 0;
}
