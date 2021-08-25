#pragma once
#include "common.h"
#include <string>
#include <typeinfo>
#include <vector>
#include <iostream>
#include <list>
#include <deque>
#include <set>
#include <stack>
#include <queue>
#include <map>

#if CXX_VER >= 2011
#  include <forward_list>
#  include <unordered_map>
#  include <unordered_set>
#  include <array>
#endif

#if HAS_OPTIONAL
#  include <optional>
#endif

#if HAS_SPAN
#  include <span>
#endif

namespace zlog
{
    template<typename T>
    inline std::string type(const T& value)
    {
        return typeid(value).name();
    }

    template<typename T>
    inline std::string type(const std::vector<T>&)
    {
        return std::string("class std::vector<") + typeid(T).name() + ">";
    }

    template<typename T>
    inline std::string type(const std::list<T>&)
    {
        return std::string("class std::list<") + typeid(T).name() + ">";
    }

    template<typename T>
    inline std::string type(const std::deque<T>&)
    {
        return std::string("class std::deque<") + typeid(T).name() + ">";
    }

    template<typename T>
    inline std::string type(const std::set<T>&)
    {
        return std::string("class std::set<") + typeid(T).name() + ">";
    }

    template<typename T>
    inline std::string type(const std::multiset<T>&)
    {
        return std::string("class std::multiset<") + typeid(T).name() + ">";
    }

    template<typename T>
    inline std::string type(const std::stack<T>&)
    {
        return std::string("class std::stack<") + typeid(T).name() + ">";
    }

    template<typename T>
    inline std::string type(const std::queue<T>&)
    {
        return std::string("class std::queue<") + typeid(T).name() + ">";
    }

    template<typename T>
    inline std::string type(const std::priority_queue<T>&)
    {
        return std::string("class std::priority_queue<") + typeid(T).name() + ">";
    }

    template<typename K, typename V>
    inline std::string type(const std::map<K, V>&)
    {
        return std::string("class std::map<") + typeid(K).name() + "," + typeid(V).name() + ">";
    }

    template<typename K, typename V>
    inline std::string type(const std::multimap<K, V>&)
    {
        return std::string("class std::multimap<") + typeid(K).name() + "," + typeid(V).name() + ">";
    }

#if CXX_VER >= 2011
    template<typename T>
    inline std::string type(const std::unordered_set<T>&)
    {
        return std::string("class std::unordered_set<") + typeid(T).name() + ">";
    }

    template<typename T>
    inline std::string type(const std::unordered_multiset<T>&)
    {
        return std::string("class std::unordered_multiset<") + typeid(T).name() + ">";
    }

    template<typename K, typename V>
    inline std::string type(const std::unordered_map<K, V>&)
    {
        return std::string("class std::unordered_map<") + typeid(K).name() + "," + typeid(V).name() + ">";
    }

    template<typename K, typename V>
    inline std::string type(const std::unordered_multimap<K, V>&)
    {
        return std::string("class std::unordered_multimap<") + typeid(K).name() + "," + typeid(V).name() + ">";
    }

    template<typename T>
    inline std::string type(const std::forward_list<T>&)
    {
        return std::string("class std::forward_list<") + typeid(T).name() + ">";
    }
#endif

    inline std::string type(const std::string&)
    {
        return "class std::string";
    }
}
