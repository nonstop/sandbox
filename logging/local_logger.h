#ifndef LOCAL_LOGGER_H
#define LOCAL_LOGGER_H

#include <sstream>

class LocalLogger
{
public:
    enum LogLevel {Error, Warning, Info, Debug};

    LocalLogger(LogLevel ll, const char* file, int line);
    virtual ~LocalLogger();

    template<typename T>
    LocalLogger& operator<<(const T& val) {
        msg_ << val;
        return *this;
    }
    static void setLogLevel(LogLevel);
private:
    LogLevel ll_;
    const char* file_;
    size_t line_;
    std::ostringstream msg_;
    static LogLevel currentLogLevel_;
};

#define LOG_INF LocalLogger(LocalLogger::Info, __FILE__, __LINE__)
#define LOG_DBG LocalLogger(LocalLogger::Debug, __FILE__, __LINE__)
#define LOG_WRN LocalLogger(LocalLogger::Warning, __FILE__, __LINE__)
#define LOG_ERR LocalLogger(LocalLogger::Error, __FILE__, __LINE__)

#endif /* LOCAL_LOGGER_H */

