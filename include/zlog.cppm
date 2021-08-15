module;
#include <Windows.h>
#ifndef Min
#  define Min(a, b) ((a) < (b) ? (a) : (b))
#endif
export module zlog;
import std.core;

export
{
    namespace lite
    {
#ifndef WINCE
        struct ConsoleTextAttribute
        {
            ConsoleTextAttribute(HANDLE handle, WORD attribute)
                : m_handle(handle)
            {
                SetConsoleTextAttribute(handle, attribute);
            }
            ~ConsoleTextAttribute()
            {
                SetConsoleTextAttribute(m_handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            HANDLE m_handle;
        };
#endif // !WINCE

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

        template<typename S>
        inline void stream(S& stream, const std::string& str, HANDLE handle, WORD attribute)
        {
            ConsoleTextAttribute textAttribute(handle, attribute);
            stream << str;
        }

        template<typename T>
        LogObject<T> operator<<(LogObject<T> obj, Expression expr)
        {
            if (obj)
            {
                stream(obj.stream(), expr.value(), GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            return obj;
        }

        template<typename T>
        LogObject<T> operator<<(LogObject<T> obj, Type type)
        {
            if (obj)
            {
                stream(obj.stream(), type.value(), GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
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
                std::string result;
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
                stream(obj.stream(), "[", GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);

                char timeStr[256] = { 0 };
                sprintf_s(timeStr, sizeof(timeStr), "%04d-%02d-%02d %02d:%02d:%02d.%03d",
                    systemTime.wYear, systemTime.wMonth, systemTime.wDay,
                    systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds);
                obj.stream() << timeStr;

                stream(obj.stream(), "] ", GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            }
            return obj;
        }

        template<typename T>
        LogObject<T> operator<<(LogObject<T> obj, std::source_location location)
        {
            if (obj)
            {
                std::string func = limitString(location.function_name(), 18);

                stream(obj.stream(), "[", GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);

                char locStr[64] = { 0 };
                sprintf_s(locStr, sizeof(locStr), "%s:% 5d",
                    func.c_str(), location.line());
                obj.stream() << locStr;

                stream(obj.stream(), "] ", GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
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
}
