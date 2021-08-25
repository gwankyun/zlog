#pragma once
#include <cstring>
#include <algorithm>
#include "zlog/common.h"
#include "zlog/source_location.hpp"
#include "zlog/marco.h"
#include "zlog/color.hpp"

#include "zlog/type.hpp"

ZLOG_EXPORT_BEGIN
namespace zlog
{
    struct Expression
    {
        Expression(std::string value)
            : m_value(value)
        {
        }
        std::string value()
        {
            return m_value;
        }
        std::string m_value;
    };

    struct Type
    {
        Type(std::string value)
            : m_value(value)
        {
        }
        std::string value()
        {
            return m_value;
        }
        std::string m_value;
    };

    inline std::string limitString(const char* str, int length)
    {
        std::string result;
        {
            char* func = new char[length];
            int len = length;
            memset(func, ' ', len);
            func[len - 1] = '\0';
            memcpy_s(func, len, str, std::min(strlen(str), static_cast<size_t>(len - 1)));
            result = func;
            delete[] func;
        }
        return result;
    }

    template<typename Output>
    class LogObject
    {
    public:
        LogObject() {}

        LogObject(Output& outpout, bool pred)
            : m_output(outpout)
            , m_pred(pred)
        {
        }

        LogObject(Output& outpout)
            : m_output(outpout)
            , m_pred(true)
        {
        }

        ~LogObject() {}

        operator bool()
        {
            return m_pred;
        }

        Output& stream()
        {
            return m_output;
        }

    private:
        Output& m_output;
        bool m_pred;
    };

    template<typename T>
    LogObject<T> operator<<(LogObject<T> obj, Color color)
    {
#if USE_CLASSIC_CONSOLE_API
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color.attribute());
        return obj;
#else
        return obj.stream() << color.ansi();
#endif
    }

    template<typename T>
    LogObject<T> operator<<(LogObject<T> obj, Expression expr)
    {
        if (obj)
        {
            obj << Color("\x1b[36m");
            obj.stream() << expr.value();
            obj << Color("\x1b[0m");
        }
        return obj;
    }

    template<typename T>
    LogObject<T> operator<<(LogObject<T> obj, Type type)
    {
        if (obj)
        {
            obj << Color("\x1b[32m");
            obj.stream() << type.value();
            obj << Color("\x1b[0m");
        }
        return obj;
    }

    template<typename S, typename It>
    inline void range(S& s, It b, It e)
    {
        s << "{ ";
        for (It i = b; i != e; ++i)
        {
            if (i != b)
            {
                s << ", ";
            }
            s << (*i);
        }
        s << " }";
    }

    template<typename S, typename It>
    inline void map(S& s, It b, It e)
    {
        s << "{ ";
        for (auto i = b; i != e; ++i)
        {
            if (i != b)
            {
                s << ", ";
            }
            s << "(" << i->first << ", " << i->second << ")";
        }
        s << " }";
    }

    template<typename T, typename U>
    LogObject<T> operator<<(LogObject<T> obj, const std::vector<U>& value)
    {
        if (obj)
        {
            range(obj.stream(), value.begin(), value.end());
        }
        return obj;
    }

#if HAS_SPAN
    template<typename T, typename U, std::size_t Extent = std::dynamic_extent>
    LogObject<T> operator<<(LogObject<T> obj, const std::span<U, Extent>& value)
    {
        if (obj)
        {
            range(obj.stream(), value.begin(), value.end());
        }
        return obj;
    }
#endif

    template<typename T, typename U>
    LogObject<T> operator<<(LogObject<T> obj, const std::set<U>& value)
    {
        if (obj)
        {
            range(obj.stream(), value.begin(), value.end());
        }
        return obj;
    }

    template<typename T, typename U>
    LogObject<T> operator<<(LogObject<T> obj, const std::multiset<U>& value)
    {
        if (obj)
        {
            range(obj.stream(), value.begin(), value.end());
        }
        return obj;
    }

#if CXX_VER >= 2011
    template<typename T, typename U>
    LogObject<T> operator<<(LogObject<T> obj, const std::forward_list<U>& value)
    {
        if (obj)
        {
            range(obj.stream(), value.begin(), value.end());
        }
        return obj;
    }

    template<typename T, typename U>
    LogObject<T> operator<<(LogObject<T> obj, const std::unordered_multiset<U>& value)
    {
        if (obj)
        {
            range(obj.stream(), value.begin(), value.end());
        }
        return obj;
    }

    template<typename T, typename U>
    LogObject<T> operator<<(LogObject<T> obj, const std::unordered_set<U>& value)
    {
        if (obj)
        {
            range(obj.stream(), value.begin(), value.end());
        }
        return obj;
    }

    template<typename T, typename U, int N>
    LogObject<T> operator<<(LogObject<T> obj, const std::array<U, N>& value)
    {
        if (obj)
        {
            range(obj.stream(), value.begin(), value.end());
        }
        return obj;
    }

    template<typename T, typename K, typename V>
    LogObject<T> operator<<(LogObject<T> obj, const std::unordered_map<K, V>& value)
    {
        if (obj)
        {
            map(obj.stream(), value.begin(), value.end());
        }
        return obj;
    }

    template<typename T, typename K, typename V>
    LogObject<T> operator<<(LogObject<T> obj, const std::unordered_multimap<K, V>& value)
    {
        if (obj)
        {
            map(obj.stream(), value.begin(), value.end());
        }
        return obj;
    }
#endif

    template<typename T, typename U>
    LogObject<T> operator<<(LogObject<T> obj, const std::list<U>& value)
    {
        if (obj)
        {
            range(obj.stream(), value.begin(), value.end());
        }
        return obj;
    }

    template<typename T, typename U>
    LogObject<T> operator<<(LogObject<T> obj, const std::deque<U>& value)
    {
        if (obj)
        {
            range(obj.stream(), value.begin(), value.end());
        }
        return obj;
    }

    template<typename O, typename S>
    inline void stack(O& o, S s)
    {
        o << "{ ";
        if (!s.empty())
        {
            o << s.top() << ", ...";
        }
        o << " }";
    }

    template<typename T, typename U>
    LogObject<T> operator<<(LogObject<T> obj, const std::stack<U>& value)
    {
        if (obj)
        {
            stack(obj.stream(), value);
        }
        return obj;
    }

    template<typename T, typename U>
    LogObject<T> operator<<(LogObject<T> obj, const std::priority_queue<U>& value)
    {
        if (obj)
        {
            stack(obj.stream(), value);
        }
        return obj;
    }

    template<typename T, typename U>
    LogObject<T> operator<<(LogObject<T> obj, const std::queue<U>& value)
    {
        if (obj)
        {
            obj.stream() << "{ ";
            if (!value.empty())
            {
                obj.stream() << value.front() << ", ... " << value.back();
            }
            obj.stream() << " }";
        }
        return obj;
    }

#if HAS_OPTIONAL
    template<typename T, typename U>
    LogObject<T> operator<<(LogObject<T> obj, const std::optional<U>& value)
    {
        if (obj)
        {
            obj.stream() << "(";
            if (value)
            {
                obj.stream() << *value;
            }
            obj.stream() << ")";
        }
        return obj;
    }
#endif

    template<typename T, typename K, typename V>
    LogObject<T> operator<<(LogObject<T> obj, const std::pair<K, V>& value)
    {
        if (obj)
        {
            obj.stream() << "(";
            obj.stream() << value.first;
            obj.stream() << ", ";
            obj.stream() << value.second;
            obj.stream() << ")";
        }
        return obj;
    }

    template<typename T, typename K, typename V>
    LogObject<T> operator<<(LogObject<T> obj, const std::map<K, V>& value)
    {
        if (obj)
        {
            map(obj.stream(), value.begin(), value.end());
        }
        return obj;
    }

    template<typename T, typename K, typename V>
    LogObject<T> operator<<(LogObject<T> obj, const std::multimap<K, V>& value)
    {
        if (obj)
        {
            map(obj.stream(), value.begin(), value.end());
        }
        return obj;
    }

    template<typename T, typename U, int N>
    LogObject<T> operator<<(LogObject<T> obj, const U value[])
    {
        if (obj)
        {
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
        }
        return obj;
    }

    template<typename T>
    LogObject<T> operator<<(LogObject<T> obj, bool value)
    {
        if (obj)
        {
            if (value)
            {
                obj.stream() << "true";
            }
            else
            {
                obj.stream() << "false";
            }
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
    LogObject<T> operator<<(LogObject<T> obj, SYSTEMTIME systemTime)
    {
        if (obj)
        {
            obj << Color("\x1b[31m");
            obj.stream() << "[";
            obj << Color("\x1b[0m");

            char timeStr[256] = { 0 };
            sprintf_s(timeStr, sizeof(timeStr), "%04d-%02d-%02d %02d:%02d:%02d.%03d",
                systemTime.wYear, systemTime.wMonth, systemTime.wDay,
                systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds);
            obj.stream() << timeStr;

            obj << Color("\x1b[31m");
            obj.stream() << "] ";
            obj << Color("\x1b[0m");
        }
        return obj;
    }

    template<typename T>
    LogObject<T> operator<<(LogObject<T> obj, typename source_location::type location)
    {
        if (obj)
        {
            std::string func = limitString(location.function_name(), 15);

            obj << Color("\x1b[32m");
            obj.stream() << "[";
            obj << Color("\x1b[0m");

            char locStr[64] = { 0 };
            sprintf_s(locStr, sizeof(locStr), "%s:% 5d",
                func.c_str(), location.line());
            obj.stream() << locStr;

            obj << Color("\x1b[32m");
            obj.stream() << "] ";
            obj << Color("\x1b[0m");
        }
        return obj;
    }

    template<typename T, typename U>
    LogObject<T> operator<<(LogObject<T> obj, U value)
    {
        if (obj)
        {
            obj.stream() << value;
        }
        return obj;
    }
}
ZLOG_EXPORT_END
