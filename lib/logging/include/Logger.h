#ifndef __Logger_h__
#define __Logger_h__

#include <Arduino.h>
#include <LogAdapter.h>

#ifdef _GLIBCXX_HAS_GTHREADS
#include <mutex>
#endif // _GLIBCXX_HAS_GTHREADS

namespace ravensnight::logging {

    #ifndef LOGBUFFER_SIZE
    #define LOGBUFFER_SIZE 256
    #endif

    #ifndef LOGGING_ENABLED
    #define LOGGING_ENABLED 0
    #endif

    #if LOGGING_ENABLED > 0
    #define LOGLEVEL_COUNT 5
    #else
    #define LOGLEVEL_COUNT 0
    #endif

    enum class LogLevel : uint8_t  {
        error = 0, 
        warn = 1,
        info = 2,
        debug = 3,
        trace = 4
    };

    /**
     * Log level function to be implemented in main application.
     */
    extern LogLevel getLogLevel(const char* category);

    class Logger {
        
        private:

            const char* _category;

            #ifdef _GLIBCXX_HAS_GTHREADS
            static std::mutex _mutex;
            #endif // _GLIBCXX_HAS_GTHREADS

            static char* _logLine;
            static LogAdapter*  _adapter;
            static const char* _prefixes[LOGLEVEL_COUNT];

        protected:

            static void write(LogLevel level, const char* category, const char* format, va_list* args);

        public:

            /** The root logger */
            static Logger root;

            /** Attach the log adapter to be used. */
            static void setup(LogAdapter* adapter);

            /** Construction */
            Logger(const char* category);

            /** Which loglevel is enabled? */
            bool isEnabled(LogLevel logLevel);

            /**
             * Logging interface
             */            
            void trace(const char* format, ...);
            void debug(const char* format, ...);
            void info(const char* format, ...);
            void warn(const char* format, ...);
            void error(const char* format, ...);
            void dump(const char* msg, const uint8_t* buffer, uint16_t bufferLen, uint8_t wrapAt);

            void entry();
            void leave();
    };

}

#endif