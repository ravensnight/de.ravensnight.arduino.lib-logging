#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <Arduino.h>

#ifdef _GLIBCXX_HAS_GTHREADS
#include <mutex>
#endif // _GLIBCXX_HAS_GTHREADS

#include <LoggerSink.h>

#ifndef LOGBUFFER_SIZE
#define LOGBUFFER_SIZE 256
#endif

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

        static void attach(LoggerSink* output);
        static void setLevel(LogLevel level);

        static void debug(const char* format, ...);
        static void info(const char* format, ...);
        static void warn(const char* format, ...);
        static void error(const char* format, ...);
        static void dump(const char* msg, const uint8_t* buffer, uint16_t bufferLen, uint8_t wrapAt);

        static boolean isEnabled(LogLevel level);        

    private:
        Logger();

        #ifdef _GLIBCXX_HAS_GTHREADS
        static std::mutex _mutex;
        #endif // _GLIBCXX_HAS_GTHREADS
        
        static LoggerSink* _output;
        static LogLevel _currentLevel;
        static char* _logLine;

        static void write(const char* prefix, const char* format, va_list&  args);

};

}

#endif // __LOGGER_H__