#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <Arduino.h>
#include <Print.h>

namespace LOGGING {

enum class LogLevel : uint8_t  {
    error = 0, 
    warn = 1,
    info = 2,
    debug = 3
};


class Logger {

    public:
        Logger(Print* target);
        void setLevel(LogLevel level);


        void debug(const char* format, ...);
        void info(const char* format, ...);
        void warn(const char* format, ...);
        void error(const char* format, ...);

        void dump(const char* msg, const uint8_t* buffer, uint16_t bufferLen, uint8_t wrapAt);

        boolean isEnabled(LogLevel level);        

        static Logger& defaultLogger();

    private:

        Print* _output;
        LogLevel _currentLevel = LogLevel::debug;

        void write(const char* prefix, const char* format, va_list&  args);

        static Logger _defaultLogger;
};

}

#endif // __LOGGER_H__