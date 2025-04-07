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

        static void attach(Print* output);
        static void setLevel(LogLevel level);
        static void debug(const char* format, ...);
        static void info(const char* format, ...);
        static void warn(const char* format, ...);
        static void error(const char* format, ...);

        static void dump(const char* msg, const uint8_t* buffer, uint16_t bufferLen, uint8_t wrapAt);

        static boolean isEnabled(LogLevel level);        

    private:
        Logger();

        static char* _buffer;
        static Print* _output;
        static LogLevel _currentLevel;

        static void write(const char* prefix, const char* format, va_list&  args);

};

}

#endif // __LOGGER_H__