#pragma once

#include <sstream>
#include <string>


namespace Toolbox
{
    class Error : public std::exception
    {
    public:
        Error(const std::string& file, long line, const std::string& functionName, const std::string& message)
            : m_message(Error::createMessage(file, line, functionName, message)) { }
        
        const char* what() const noexcept
        {
            return m_message;
        }

    private:
        const char* m_message;

        static const char* createMessage(const std::string& file, long line, const std::string& functionName, const std::string& message)
        {
            std::ostringstream os;
            os << "Error: " << functionName << ":\n  " << file << "(" << line << "): \n" << message;
            return os.str().c_str();
        }
    };

}

#define TB_ENSURE(condition,message) \
if (!(condition)) { \
    std::ostringstream __os__; \
    __os__ << message; \
    throw Toolbox::Error(__FILE__, __LINE__, __func__, __os__.str()); \
 } else 

#define TB_ENSURE_QUICK(condition,message) \
if (!(condition)) { \
    throw Toolbox::Error(__FILE__, __LINE__, __func__, message); \
 } else 

#define TB_THROW(message) TB_ENSURE(false, message)
