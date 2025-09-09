#include <ClassLogger.h>

namespace ravensnight::logging {

    ClassLogger::ClassLogger(const char* category) {
        _category = category;
    }

    bool ClassLogger::isEnabled(LogLevel logLevel) {        
        #if(LOGGING_ENABLED > 0)
            LogLevel catLevel = getLogLevel(_category);
            return (logLevel <= catLevel);
        #else
            return false;
        #endif
    }

    void ClassLogger::trace(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::trace)) {
                Logger::write(LogLevel::trace, _category, format, &args);
            }
            va_end( args );
        #endif
    }

    void ClassLogger::debug(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::debug)) {
                Logger::write(LogLevel::debug, _category, format, &args);
            }
            va_end( args );
        #endif
    }
    
    void ClassLogger::info(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::info)) {
                Logger::write(LogLevel::info, _category, format, &args);
            }
            va_end( args );
        #endif
    }
    
    void ClassLogger::warn(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::warn)) {
                Logger::write(LogLevel::warn, _category, format, &args);
            }
            va_end( args );
        #endif
    }
    
    void ClassLogger::error(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::error)) {
                Logger::write(LogLevel::error, _category, format, &args);
            }
            va_end( args );
        #endif
    }
    
    void ClassLogger::dump(const char* msg, const uint8_t* buffer, uint16_t bufferLen, uint8_t wrapAt) {
        #if(LOGGING_ENABLED > 0)
            if (isEnabled(LogLevel::trace)) {
                Logger::dump(msg, buffer, bufferLen, wrapAt);
            }
        #endif
    }

    void ClassLogger::entry() {
        #if(LOGGING_ENABLED > 0) 
            if (isEnabled(LogLevel::trace)) {
                Logger::write(LogLevel::trace, _category, "entry.", 0);
            }
        #endif
    }

    void ClassLogger::leave() {
        #if(LOGGING_ENABLED > 0) 
            if (isEnabled(LogLevel::trace)) {
                Logger::write(LogLevel::trace, _category, "leave.", 0);
            }
        #endif
    }
}
