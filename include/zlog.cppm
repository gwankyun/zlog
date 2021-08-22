module;
#include "zlog/common.h"
export module zlog;
import std.core;
import zlog.color;
import zlog.source_location;

ZLOG_EXPORT_BEGIN
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
    inline std::string type(const std::set<T>&)
    {
        return std::string("class std::set<") + typeid(T).name() + ">";
    }

    //template<typename T, int N>
    //inline std::string type(const std::array<T, N>&)
    //{
    //    return std::string("std::array<") + typeid(T).name() + "," + std::to_string(N) + ">";
    //}

    template<typename K, typename V>
    inline std::string type(const std::map<K, V>&)
    {
        return std::string("class std::map<") + typeid(K).name() + "," + typeid(V).name() + ">";
    }

    inline std::string type(const std::string&)
    {
        return "class std::string";
    }

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
            memcpy_s(func, len, str, Min(strlen(str), len - 1));
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
        s << "{";
        for (It i = b; i != e; ++i)
        {
            if (i != b)
            {
                s << ", ";
            }
            s << (*i);
        }
        s << "}";
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
    LogObject<T> operator<<(LogObject<T> obj, const std::list<U>& value)
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

    //template<typename T, typename K, typename V>
    //LogObject<T> operator<<(LogObject<T> obj, const std::pair<K, V>& value)
    //{
    //    if (obj)
    //    {
    //        obj.stream() << "(";
    //        obj.stream() << value.first;
    //        obj.stream() << ", ";
    //        obj.stream() << value.second;
    //        obj.stream() << ")";
    //    }
    //    return obj;
    //}

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
            obj.stream() << "{";
            for (auto i = value.begin(); i != value.end(); ++i)
            {
                if (i != value.begin())
                {
                    obj.stream() << ", ";
                }
                obj.stream() << "(" << i->first << ", " << i->second << ")";
            }
            obj.stream() << "}";
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
            std::string func = limitString(location.function_name(), 18);

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
