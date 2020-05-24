#pragma once

#define CPP_PRICING_TOOLBOX_ENABLE_ASSERT 1

#include <cassert>
#include <string>


namespace Toolbox
{
    class Error : public std::exception
    {
    public:
        Error(const std::string& file, long line, const std::string& functionName, const std::string& message)
            : m_message(Error::createMessage(file, line, functionName, message)) { }

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
        std::string m_message;

        static std::string createMessage(const std::string& file, long line, const std::string& functionName, const std::string& message)
        {
            return Error::Msg() << "Error: " << functionName << ":\n  " << file << "(" << line << "): \n" << message;
        }
    };

    inline bool TB_ASSERT_MESSAGE(const char* /* msg */)
    {
        return false;
    }
}

#if CPP_PRICING_TOOLBOX_ENABLE_ASSERT
    #define TB_ASSERT(expr, msg) assert((expr) || Toolbox::TB_ASSERT_MESSAGE(msg))
#else
    #define TB_ASSERT(expr, msg)
#endif

#define TB_ENSURE(condition,message) \
if (!(condition)) { \
    throw Toolbox::Error(__FILE__, __LINE__, __func__, Error::Msg() << message); \
 } else

#define TB_THROW(message) TB_ENSURE(false, message)
