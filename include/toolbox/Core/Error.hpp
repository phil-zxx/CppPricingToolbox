#pragma once

#include <cassert>
#include <string>


namespace Toolbox
{
    struct ErrorOS
    {
        ErrorOS() = default;

        template<class T>
        ErrorOS& operator<<(const T i)
        {
            m_str.append(std::to_string(i));
            return *this;
        }

        ErrorOS& operator<<(const char* msg)
        {
            m_str.append(msg);
            return *this;
        }

        operator std::string() const
        {
            return m_str;
        }

        std::string m_str;
    };
}

#ifdef NDEBUG
    #define TB_ASSERT(expr, msg)
#else
    #define TB_ASSERT(expr, msg) assert((expr) || !msg)
#endif

#define TB_ENSURE(condition, message) \
    if (!(condition)) { \
        throw std::runtime_error(Toolbox::ErrorOS() << "Error: " << __func__ << ":\n  " << __FILE__ << "(" << __LINE__ << "): \n" << message); \
     } else

#define TB_THROW(message) TB_ENSURE(false, message)
