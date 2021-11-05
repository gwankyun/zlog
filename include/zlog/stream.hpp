#pragma once

namespace zlog
{
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

    template<typename O, typename S>
    inline void stack(O& o, S s)
    {
        o << "{ ";
        if (!s.empty())
        {
            o << s.top() << ", ...";
        }
        o << " }";
        o << " [";
        o << s.size();
        o << "]";
    }
    template<typename Output>
    class Stream
    {
    public:
        Stream() {}

        Stream(Output& outpout, bool pred)
            : m_output(outpout)
            , m_pred(pred)
            , first(true)
        {
        }

        Stream(Output& outpout)
            : m_output(outpout)
            , m_pred(true)
            , first(true)
        {
        }

        ~Stream() {}

        operator bool()
        {
            return m_pred;
        }

        Output& stream()
        {
            return m_output;
        }

        template<typename It>
        inline Stream range(It b, It e)
        {
            if (*this)
            {
                zlog::range(stream(), b, e);
            }
            return *this;
        }

        template<typename Cont>
        inline Stream range(const Cont& c)
        {
            return range(c.begin(), c.end());
        }

        template<typename It>
        inline Stream map(It b, It e)
        {
            if (*this)
            {
                zlog::map(stream(), b, e);
            }
            return *this;
        }

        template<typename Cont>
        inline Stream map(const Cont& c)
        {
            return map(c.begin(), c.end());
        }

        template<typename S>
        inline Stream stack(S s)
        {
            if (*this)
            {
                zlog::stack(stream(), s);
            }
            return *this;
        }

        //CONSOLE_SCREEN_BUFFER_INFO info;
        WORD info;
        bool first;

    private:
        Output& m_output;
        bool m_pred;
    };

    inline bool findColor(const std::string& str, std::pair<std::string, WORD>& result)
    {
        typedef std::vector< std::pair<std::string, WORD> > vecType;
        vecType vec;
        vec.push_back(std::make_pair<std::string, WORD>("\x1b[32m", FOREGROUND_GREEN | FOREGROUND_INTENSITY));
        vec.push_back(std::make_pair<std::string, WORD>("\x1b[36m", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
        vec.push_back(std::make_pair<std::string, WORD>("\x1b[31m", FOREGROUND_RED));
        vec.push_back(std::make_pair<std::string, WORD>("\x1b[01m", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
        vec.push_back(std::make_pair<std::string, WORD>("\x1b[0m", 0));

        for (vecType::const_iterator i = vec.begin(); i != vec.end(); ++i)
        {
            size_t idx = str.find(i->first);
            if (idx != std::string::npos)
            {
                result = *i;
                return true;
            }
        }

        return false;
    }

    template<typename T>
    Stream<T> operator<<(Stream<T> obj, std::string str)
    {
        if (!obj)
        {
            return obj;
        }

        std::pair<std::string, WORD> result;
        if (findColor(str, result))
        {
            size_t idx = str.find(result.first);
            if (idx != 0)
            {
                std::string head(str.substr(0, idx));
                return obj << head << str.substr(idx);
            }

            if (result.first != std::string("\x1b[0m"))
            {
                if (obj.first)
                {
                    CONSOLE_SCREEN_BUFFER_INFO buffer;
                    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer);
                    obj.info = buffer.wAttributes;
                    obj.first = false;
                }
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), result.second);
            }
            else
            {
                //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), obj.info);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }

            std::string sub(str.substr(idx + result.first.size()));
            return obj << sub;
        }
        else
        {
            obj.stream() << str;
            return obj;
        }
    }

}
