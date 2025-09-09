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
#define LOGGING_ENABLED 0
#define LOGLEVEL_COUNT 0
#else
#define LOGGING_ENABLED 1
#define LOGLEVEL_COUNT 5
#endif

#define LOGBUFFER_DUMP_OFFSET 5

namespace ravensnight::logging {

#define LOG_CATERGORY_ROOT 0

enum class LogLevel : uint8_t  {
    error = 0, 
    warn = 1,
    info = 2,
    debug = 3,
    trace = 4
};


/**
 * RootLogger
 */
class Logger {

    friend class Loggable;

    public:

        static void attach(LoggerSink* output);

        static void trace(const char* format, ...);
        static void debug(const char* format, ...);
        static void info(const char* format, ...);
        static void warn(const char* format, ...);
        static void error(const char* format, ...);
        static void dump(const char* msg, const uint8_t* buffer, uint16_t bufferLen, uint8_t wrapAt);

        static void log(LogLevel level, const char* format, ...);

        static bool isEnabled(LogLevel level);        
        static void setLevel(LogLevel level);

    protected:
        static void write(LogLevel level, const char* format, ...);

    private:
        Logger();

        #ifdef _GLIBCXX_HAS_GTHREADS
        static std::mutex _mutex;
        #endif // _GLIBCXX_HAS_GTHREADS

        static LoggerSink*  _output;
        static char*        _logLine;
        static LogLevel     _rootLevel;

        static const char* _prefixes[LOGLEVEL_COUNT];
};

}

#endif // __LOGGER_H__