#pragma once
#include <cstring>
#include <algorithm>
#include <sstream>
#include "zlog/common.h"
#include "zlog/source_location.hpp"
#include "zlog/marco.h"
#include "zlog/type.hpp"
#include "zlog/stream.hpp"

ZLOG_EXPORT_BEGIN
namespace zlog
{
    inline std::string limitString(const char* str, int length)
    {
        std::string result(str);
        if (result.size() > length)
        {
            return result.substr(0, length);
        }
        else
        {
            return result + std::string(length - result.size(), ' ');
        }
    }

    template<typename T>
    Stream<T> operator<<(Stream<T> obj, const char* str)
    {
        obj << std::string(str);
        return obj;
    }

    template<typename T, typename U>
    Stream<T> operator<<(Stream<T> obj, const std::vector<U>& value)
    {
        return obj.range(value);
    }

#if HAS_SPAN
    template<typename T, typename U, std::size_t Extent = std::dynamic_extent>
    Stream<T> operator<<(Stream<T> obj, const std::span<U, Extent>& value)
    {
        return obj.range(value);
    }
#endif

    template<typename T, typename U>
    Stream<T> operator<<(Stream<T> obj, const std::set<U>& value)
    {
        return obj.range(value);
    }

    template<typename T, typename U>
    Stream<T> operator<<(Stream<T> obj, const std::multiset<U>& value)
    {
        return obj.range(value);
    }

#if CXX_VER >= 2011
    template<typename T, typename U>
    Stream<T> operator<<(Stream<T> obj, const std::forward_list<U>& value)
    {
        return obj.range(value);
    }

    template<typename T, typename U>
    Stream<T> operator<<(Stream<T> obj, const std::unordered_multiset<U>& value)
    {
        return obj.range(value);
    }

    template<typename T, typename U>
    Stream<T> operator<<(Stream<T> obj, const std::unordered_set<U>& value)
    {
        return obj.range(value);
    }

    template<typename T, typename U, int N>
    Stream<T> operator<<(Stream<T> obj, const std::array<U, N>& value)
    {
        return obj.range(value);
    }

    template<typename T, typename K, typename V>
    Stream<T> operator<<(Stream<T> obj, const std::unordered_map<K, V>& value)
    {
        return obj.map(value);
    }

    template<typename T, typename K, typename V>
    Stream<T> operator<<(Stream<T> obj, const std::unordered_multimap<K, V>& value)
    {
        return obj.map(value);
    }
#endif

    template<typename T, typename U>
    Stream<T> operator<<(Stream<T> obj, const std::list<U>& value)
    {
        return obj.range(value);
    }

    template<typename T, typename U>
    Stream<T> operator<<(Stream<T> obj, const std::deque<U>& value)
    {
        return obj.range(value);
    }

    template<typename T, typename U>
    Stream<T> operator<<(Stream<T> obj, const std::stack<U>& value)
    {
        return obj.stack(value);
    }

    template<typename T, typename U>
    Stream<T> operator<<(Stream<T> obj, const std::priority_queue<U>& value)
    {
        return obj.stack(value);
    }

    template<typename T, typename U>
    Stream<T> operator<<(Stream<T> obj, const std::queue<U>& value)
    {
        if (!obj)
        {
            return obj;
        }
        obj.stream() << "{ ";
        if (!value.empty())
        {
            obj.stream() << value.front() << ", ... " << value.back();
        }
        obj.stream() << " }";
        return obj;
    }

#if HAS_OPTIONAL
    template<typename T, typename U>
    Stream<T> operator<<(Stream<T> obj, const std::optional<U>& value)
    {
        if (!obj)
        {
            return obj;
        }
        obj.stream() << "(";
        if (value)
        {
            obj.stream() << *value;
        }
        obj.stream() << ")";
        return obj;
    }
#endif

    template<typename T, typename K, typename V>
    Stream<T> operator<<(Stream<T> obj, const std::pair<K, V>& value)
    {
        if (!obj)
        {
            return obj;
        }
        obj.stream() << "(";
        obj.stream() << value.first;
        obj.stream() << ", ";
        obj.stream() << value.second;
        obj.stream() << ")";
        return obj;
    }

    template<typename T, typename K, typename V>
    Stream<T> operator<<(Stream<T> obj, const std::map<K, V>& value)
    {
        return obj.map(value);
    }

    template<typename T, typename K, typename V>
    Stream<T> operator<<(Stream<T> obj, const std::multimap<K, V>& value)
    {
        return obj.map(value);
    }

    template<typename T, typename U, int N>
    Stream<T> operator<<(Stream<T> obj, const U value[])
    {
        if (!obj)
        {
            return obj;
        }
        obj.stream() << "{";
        for (size_t i = 0; i < N; i++)
        {
            if (i != N - 1)
            {
                obj.stream() << value[i] << ", ";
            }
            else
            {
                obj.stream() << value[i];
            }
        }
        obj.stream() << "}";
        return obj;
    }

    template<typename T>
    Stream<T> operator<<(Stream<T> obj, bool value)
    {
        if (!obj)
        {
            return obj;
        }

        if (value)
        {
            obj.stream() << "true";
        }
        else
        {
            obj.stream() << "false";
        }
        return obj;
    }

    inline SYSTEMTIME currentTime()
    {
        SYSTEMTIME systemTime;
        GetLocalTime(&systemTime);
        return systemTime;
    }

    template<typename T>
    Stream<T> operator<<(Stream<T> obj, SYSTEMTIME systemTime)
    {
        if (!obj)
        {
            return obj;
        }

        {
            //obj.stream() << Color("\x1b[31m");
            obj.stream() << "[";
        }

        char timeStr[256] = { 0 };
        sprintf_s(timeStr, sizeof(timeStr), "%04d-%02d-%02d %02d:%02d:%02d.%03d",
            systemTime.wYear, systemTime.wMonth, systemTime.wDay,
            systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds);
        obj.stream() << timeStr;

        {
            //obj.stream() << Color("\x1b[31m");
            obj.stream() << "] ";
        }
        return obj;
    }

    template<typename T>
    Stream<T> operator<<(Stream<T> obj, typename source_location::type location)
    {
        if (!obj)
        {
            return obj;
        }

        std::string func = limitString(location.function_name(), 10);

        {
            //obj.stream() << Color("\x1b[32m");
            obj.stream() << "[";
        }

        char locStr[64] = { 0 };
        sprintf_s(locStr, sizeof(locStr), "%s:% 5d",
            func.c_str(), location.line());
        obj.stream() << locStr;

        {
            //obj.stream() << Color("\x1b[32m");
            obj.stream() << "] ";
        }
        return obj;
    }

    template<typename T>
    inline std::string value(T value)
    {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    template<typename T, typename U>
    Stream<T> operator<<(Stream<T> obj, U value)
    {
        if (obj)
        {
            obj.stream() << value;
        }
        return obj;
    }
}
ZLOG_EXPORT_END
