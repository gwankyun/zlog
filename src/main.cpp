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
    std::vector<int> vec{ 1, 2, 3 };
    ZDBG(vec);
    std::list<int> lst{ 1, 2, 3 };
    ZDBG(lst);
    std::array<int, 3> arr{ 1, 2, 3 };
    ZDBG(arr);
    std::pair<int, int> p(1, 2);
    ZDBG(p);
    std::map<int, int> m;
    m[1] = 1;
    m[2] = 2;
    m[3] = 3;
    ZDBG(m);
    std::set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    ZDBG(s);
    std::optional<int> o(1);
    ZDBG(o);
    std::deque<int> d{ 1, 2, 3 };
    ZDBG(d);

    std::stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    ZDBG(st);

    //int a[3];
    //a[0] = 1;
    //a[1] = 2;
    //a[2] = 3;
    //ZDBG(a);
    return 0;
}
