#include <Loggable.h>

namespace ravensnight::logging {

    Loggable::Loggable(uint16_t category) {
        _category = category;
    }

    bool Loggable::isEnabled(LogLevel logLevel) {        
        #if(LOGGING_ENABLED > 0)
            LogLevel catLevel = getLogLevel(_category);
            return (logLevel <= catLevel);
        #else
            return false;
        #endif
    }

    void Loggable::trace(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::trace)) {
                Logger::log(LogLevel::trace, format, args);
            }
            va_end( args );
        #endif
    }

    void Loggable::debug(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::debug)) {
                Logger::log(LogLevel::debug, format, args);
            }
            va_end( args );
        #endif
    }
    
    void Loggable::info(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::info)) {
                Logger::log(LogLevel::info, format, args);
            }
            va_end( args );
        #endif
    }
    
    void Loggable::warn(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::warn)) {
                Logger::log(LogLevel::warn, format, args);
            }
            va_end( args );
        #endif
    }
    
    void Loggable::error(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::error)) {
                Logger::log(LogLevel::error, format, args);
            }
            va_end( args );
        #endif
    }
    
    void Loggable::dump(const char* msg, const uint8_t* buffer, uint16_t bufferLen, uint8_t wrapAt) {
        #if(LOGGING_ENABLED > 0)
            if (isEnabled(LogLevel::debug)) {
                Logger::dump(msg, buffer, bufferLen, wrapAt);
            }
        #endif
    }

}
