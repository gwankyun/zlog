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

    std::cout << "\n";

    std::pair<int, int> p(1, 2);
    ZDBG(p);
    std::optional<int> o(1);
    ZDBG(o);

    std::cout << "\n";

    std::array<int, 3> arr{ 1, 2, 3 };
    ZDBG(arr);

    std::vector<int> vec{ 1, 2, 3 };
    ZDBG(vec);

    std::deque<int> d{ 1, 2, 3 };
    ZDBG(d);

    std::forward_list<int> fl{ 1, 2, 3 };
    ZDBG(fl);

    std::list<int> lst{ 1, 2, 3 };
    ZDBG(lst);

    std::cout << "\n";

    std::set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    ZDBG(s);

    std::map<int, int> m;
    m[1] = 1;
    m[2] = 2;
    m[3] = 3;
    ZDBG(m);

    std::multiset<int> ms;
    ms.insert(1);
    ms.insert(2);
    ms.insert(3);
    ms.insert(1);
    ZDBG(ms);

    std::multimap<int, int> mm;
    mm.insert({ 1, 1 });
    mm.insert({ 2, 2 });
    mm.insert({ 3, 3 });
    mm.insert({ 1, 3 });
    ZDBG(mm);

    std::cout << "\n";

    std::unordered_set<int> us;
    us.insert(1);
    us.insert(2);
    us.insert(3);
    ZDBG(us);

    std::unordered_map<int, int> um;
    um[1] = 1;
    um[2] = 2;
    um[3] = 3;
    ZDBG(um);

    std::unordered_multiset<int> ums;
    ums.insert(1);
    ums.insert(2);
    ums.insert(3);
    ums.insert(1);
    ZDBG(ums);

    std::unordered_multimap<int, int> umm;
    umm.insert({ 1, 1 });
    umm.insert({ 2, 2 });
    umm.insert({ 3, 3 });
    umm.insert({ 1, 3 });
    ZDBG(umm);

    std::cout << "\n";

    std::stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    ZDBG(st);

    std::queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    ZDBG(q);

    std::priority_queue<int> pq;
    pq.push(1);
    pq.push(3);
    pq.push(2);
    ZDBG(pq);

    std::cout << "\n";

    int a[3];
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    ZDBG(std::span(a));
    return 0;
}
