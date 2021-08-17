#pragma once
//#ifdef _WIN32
//#  include <Windows.h>
//#endif
#include <cstring>
#include <typeinfo>
#include <vector>
#include <iostream>
#include "zlog/common.h"
#include "zlog/source_location.hpp"
#include "zlog/marco.h"
#include "zlog/color.hpp"

//#ifndef Min
//#  define Min(a, b) ((a) < (b) ? (a) : (b))
//#endif

//#ifndef EXPORT_BEGIN
//#  define EXPORT_BEGIN
//#endif
//
//#ifndef EXPORT_END
//#  define EXPORT_END
//#endif

//#ifndef USE_CLASSIC_CONSOLE_API
//#  if defined(_WIN32)
//#    define USE_CLASSIC_CONSOLE_API 1
//#  else
//#    define USE_CLASSIC_CONSOLE_API 0
//#  endif
//#endif

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
        return std::string("std::vector<") + typeid(T).name() + ">";
    }

    inline std::string type(const std::string&)
    {
        return "std::string";
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

    template<typename T, typename U>
    LogObject<T> operator<<(LogObject<T> obj, std::vector<U> value)
    {
        if (obj)
        {
            std::string result;
            obj.stream() << "{";
            for (size_t i = 0; i < value.size(); i++)
            {
                if (i != value.size() - 1)
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
