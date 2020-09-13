#pragma once

#include <cassert>
#include <sstream>
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

    private:
        const std::string m_message;

        static std::string createMessage(const std::string& file, long line, const std::string& functionName, const std::string& message)
        {
            std::ostringstream os;
            os << "Error: " << functionName << ":\n  " << file << "(" << line << "): \n" << message;
            return os.str();
        }
    };
}

#ifdef NDEBUG
    #define TB_ASSERT(expr, msg)
#else
    #define TB_ASSERT(expr, msg) assert((expr) || !msg)
#endif

#define TB_ENSURE(condition, message) \
    if (!(condition)) { \
        std::ostringstream __os__; \
        __os__ << message; \
        throw Toolbox::Error(__FILE__, __LINE__, __func__, __os__.str()); \
     } else

#define TB_THROW(message) TB_ENSURE(false, message)
