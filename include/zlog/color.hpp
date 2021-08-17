#pragma once
#ifdef _WIN32
#  include <Windows.h>
#endif
#include <string>
#include "zlog/module.h"

ZLOG_EXPORT_BEGIN
namespace zlog
{
    struct Color
    {
        Color(const char* _color)
        {
            m_code = _color;
            if (m_code == "\x1b[32m")
            {
                m_attribute = FOREGROUND_GREEN;
            }
            else if (m_code == "\x1b[36m")
            {
                m_attribute = FOREGROUND_GREEN | FOREGROUND_BLUE;
            }
            else if (m_code == "\x1b[31m")
            {
                m_attribute = FOREGROUND_RED;
            }
            else
            {
                m_attribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            }
        }

        ~Color() {}

        std::string ansi()
        {
            return m_code;
        }

        WORD attribute()
        {
            return m_attribute;
        }

    private:
        std::string m_code;
        WORD m_attribute;
    };
}
ZLOG_EXPORT_END
