#include <Logger.h>

namespace ravensnight::logging {

    #define LOGBUFFER_DUMP_OFFSET 6

    #ifdef _GLIBCXX_HAS_GTHREADS
    std::mutex Logger::_mutex;
    #endif 

    // define the global serial logger
    Logger Logger::root("RootLogger");
    LogAdapter* Logger::_adapter = 0;
    char* Logger::_logLine = (char*)malloc(LOGBUFFER_SIZE + 1);

    #if (LOGGING_ENABLED > 0)
    const char* Logger::_prefixes[LOGLEVEL_COUNT] = {
        "error",
        "warn",
        "info",
        "debug",
        "trace"
    };
    #endif

    Logger::Logger(const char* category) {
        _category = category;
    }

    bool Logger::isEnabled(LogLevel logLevel) {        
        #if(LOGGING_ENABLED > 0)
            LogLevel catLevel = getLogLevel(_category);
            return (logLevel <= catLevel);
        #else
            return false;
        #endif
    }

    void Logger::write(LogLevel level, const char* category, const char* format, va_list* args) {
        #if (LOGGING_ENABLED > 0)
            #ifdef _GLIBCXX_HAS_GTHREADS
            const std::lock_guard<std::mutex> lock(_mutex);
            #endif 

            // output NULL?
            if (_adapter == 0) {
                return;
            };
            
            const char* prefix = _prefixes[(uint8_t)level];
            const char* cat = category == 0 ? "RootLogger" : category;

            sprintf(_logLine, "[%s::%s] ", cat, prefix);

            if (args == 0) {
                sprintf(_logLine + strlen(_logLine), format);
            } else {
                vsprintf(_logLine + strlen(_logLine), format, *args);
            }
            _adapter->out(_logLine);

        #endif
    }

    void Logger::trace(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::trace)) {
                write(LogLevel::trace, _category, format, &args);
            }
            va_end( args );
        #endif
    }

    void Logger::debug(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::debug)) {
                write(LogLevel::debug, _category, format, &args);
            }
            va_end( args );
        #endif
    }
    
    void Logger::info(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::info)) {
                write(LogLevel::info, _category, format, &args);
            }
            va_end( args );
        #endif
    }
    
    void Logger::warn(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::warn)) {
                write(LogLevel::warn, _category, format, &args);
            }
            va_end( args );
        #endif
    }
    
    void Logger::error(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::error)) {
                write(LogLevel::error, _category, format, &args);
            }
            va_end( args );
        #endif
    }
    
    void Logger::dump(const char* msg, const uint8_t* buffer, uint16_t bufferLen, uint8_t wrapAt) {
        #if(LOGGING_ENABLED > 0)

            #ifdef _GLIBCXX_HAS_GTHREADS
            const std::lock_guard<std::mutex> lock(_mutex);
            #endif 

            if ((_adapter == 0) || (!isEnabled(LogLevel::trace))) {
                return;
            }

            uint8_t wrap = wrapAt;

            // prepare length
            if (wrap > 0) {
                if (wrap > (LOGBUFFER_SIZE - (1 + LOGBUFFER_DUMP_OFFSET))) {
                    wrap = (LOGBUFFER_SIZE - (1 + LOGBUFFER_DUMP_OFFSET));
                }
            } else {
                wrap = LOGBUFFER_SIZE - (LOGBUFFER_DUMP_OFFSET + 1);
            }

            // print first line
            sprintf(_logLine, "[%s:dump] %s (length: %d):", _category, msg, bufferLen);
            _adapter->out(_logLine);

            // print bytes
            uint8_t offset = 0;
            for (uint16_t i = 0; i < bufferLen; i++) {

                if ((i > 0) && ((i % wrap) == 0)) {
                    _adapter->out(_logLine);
                    offset = 0;
                }

                // print line number
                if (offset == 0) {
                    sprintf(_logLine, "%04X: ", i / wrap);
                    offset += LOGBUFFER_DUMP_OFFSET;
                }

                // print block
                sprintf((_logLine + offset), "%02X ", buffer[i]);
                offset += 3;

            }

            if (offset > 0) {
                _adapter->out(_logLine);        
            }
        #endif            
    }

    void Logger::entry() {
        #if(LOGGING_ENABLED > 0) 
            if (isEnabled(LogLevel::trace)) {
                write(LogLevel::trace, _category, "entry.", 0);
            }
        #endif
    }

    void Logger::leave() {
        #if(LOGGING_ENABLED > 0) 
            if (isEnabled(LogLevel::trace)) {
                write(LogLevel::trace, _category, "leave.", 0);
            }
        #endif
    }

    void Logger::setup(LogAdapter* output) {
        Logger::_adapter = output;
    }

}
