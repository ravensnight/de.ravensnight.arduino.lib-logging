#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <Arduino.h>
#include <Print.h>

#ifndef LOGGING_ENABLED
#define LOGGING_ENABLED 1
#endif

namespace LOGGING {

enum class LogLevel : uint8_t  {
    error = 0, 
    warn = 1,
    info = 2,
    debug = 3
};


class Logger {

    public:

        static Logger instance;

        void attach(Print* output);

        void setLevel(LogLevel level);
        void debug(const char* format, ...);
        void info(const char* format, ...);
        void warn(const char* format, ...);
        void error(const char* format, ...);

        void dump(const char* msg, const uint8_t* buffer, uint16_t bufferLen, uint8_t wrapAt);

        boolean isEnabled(LogLevel level);        

    private:
        Logger();

        Print* _output;
        LogLevel _currentLevel = LogLevel::debug;

        void write(const char* prefix, const char* format, va_list&  args);

};

}

#endif // __LOGGER_H__