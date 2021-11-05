#pragma once
#include "common.h"
#include <string>
#include <typeinfo>
#include <vector>
#include <iostream>
#include <list>
#include <deque>
#include <utility>
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
    inline std::string vectorType(const std::string& cont)
    {
        return cont + "<" + typeid(T).name() + ">";
    }

    template<typename T, int N>
    inline std::string arrayType(const std::string& cont)
    {
        return cont + "<" + typeid(T).name() + "," + std::to_string(N) + ">";
    }

    template<typename K, typename V>
    inline std::string mapType(const std::string& cont)
    {
        return cont + "<" + typeid(K).name() + "," + typeid(V).name() + ">";
    }

    template<typename T>
    inline std::string type(const T& value)
    {
        return typeid(value).name();
    }

    template<typename K, typename V>
    inline std::string type(const std::pair<K, V>&)
    {
        return std::string("std::pair") + "<" + typeid(K).name() + "," + typeid(V).name() + ">";
    }

    template<typename T>
    inline std::string type(const std::vector<T>&)
    {
        return vectorType<T>("std::vector");
    }

    template<typename T>
    inline std::string type(const std::list<T>&)
    {
        return vectorType<T>("std::list");
    }

    template<typename T>
    inline std::string type(const std::deque<T>&)
    {
        return vectorType<T>("std::deque");
    }

    template<typename T>
    inline std::string type(const std::set<T>&)
    {
        return vectorType<T>("std::set");
    }

    template<typename T>
    inline std::string type(const std::multiset<T>&)
    {
        return vectorType<T>("std::multiset");
    }

    template<typename T>
    inline std::string type(const std::stack<T>&)
    {
        return vectorType<T>("std::stack");
    }

    template<typename T>
    inline std::string type(const std::queue<T>&)
    {
        return vectorType<T>("std::queue");
    }

    template<typename T>
    inline std::string type(const std::priority_queue<T>&)
    {
        return vectorType<T>("std::priority_queue");
    }

    template<typename K, typename V>
    inline std::string type(const std::map<K, V>&)
    {
        return mapType<K, V>("std::map");
    }

    template<typename K, typename V>
    inline std::string type(const std::multimap<K, V>&)
    {
        return mapType<K, V>("std::multimap");
    }

#if CXX_VER >= 2011
    template<typename T, int N>
    inline std::string type(const std::array<T, N>&)
    {
        return arrayType<T, N>("std::array");
    }

    template<typename T>
    inline std::string type(const std::unordered_set<T>&)
    {
        return vectorType<T>("std::unordered_set");
    }

    template<typename T>
    inline std::string type(const std::unordered_multiset<T>&)
    {
        return vectorType<T>("std::unordered_multiset");
    }

    template<typename K, typename V>
    inline std::string type(const std::unordered_map<K, V>&)
    {
        return mapType<K, V>("std::unordered_map");
    }

    template<typename K, typename V>
    inline std::string type(const std::unordered_multimap<K, V>&)
    {
        return mapType<K, V>("std::unordered_multimap");
    }

    template<typename T>
    inline std::string type(const std::forward_list<T>&)
    {
        return vectorType<T>("std::forward_list");
    }
#endif

#if HAS_SPAN
    template<typename T, int N>
    inline std::string type(const std::span<T, N>&)
    {
        return arrayType<T, N>("std::span");
    }
#endif

#if HAS_OPTIONAL
    template<typename T>
    inline std::string type(const std::optional<T>&)
    {
        return std::string("std::optional") + "<" + typeid(T).name() + ">";
    }
#endif

    inline std::string type(const std::string&)
    {
        return "std::string";
    }
}
