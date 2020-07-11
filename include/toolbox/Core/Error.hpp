#pragma once

#include <cassert>
#include <string>


namespace Toolbox
{
    class Error : public std::exception
    {
    public:
        Error(const std::string& file, long line, const std::string& functionName, const std::string& message)
            : m_message("Error: " + functionName + ":\n  " + file + "(" + std::to_string(line) + "): \n" + message) { }

        const char* what() const noexcept override
        {
            return m_message.c_str();
        }

        struct Msg
        {
            Msg() = default;

           template<class T>
            Msg& operator<<(T i)
            {
                m_str.append(std::to_string(i));
                return *this;
            }

            Msg& operator<<(const char* msg)
            {
                m_str.append(msg);
                return *this;
            }

            Msg& operator<<(const std::string& msg)
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

    private:
        const std::string m_message;
    };
}

#ifdef NDEBUG
    #define TB_ASSERT(expr, msg)
#else
    #define TB_ASSERT(expr, msg) assert((expr) || !msg)
#endif

#define TB_ENSURE(condition,message) \
    if (!(condition)) { \
        throw Toolbox::Error(__FILE__, __LINE__, __func__, Error::Msg() << message); \
     } else

#define TB_THROW(message) TB_ENSURE(false, message)
