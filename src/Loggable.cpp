#include <Loggable.h>

namespace ravensnight::logging {

    Loggable::Loggable(const char* category) {
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
                Logger::write(LogLevel::trace, _category, format, args);
            }
            va_end( args );
        #endif
    }

    void Loggable::debug(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::debug)) {
                Logger::write(LogLevel::debug, _category, format, args);
            }
            va_end( args );
        #endif
    }
    
    void Loggable::info(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::info)) {
                Logger::write(LogLevel::info, _category, format, args);
            }
            va_end( args );
        #endif
    }
    
    void Loggable::warn(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::warn)) {
                Logger::write(LogLevel::warn, _category, format, args);
            }
            va_end( args );
        #endif
    }
    
    void Loggable::error(const char* format, ...) {
        #if(LOGGING_ENABLED > 0)
            va_list args;
            va_start( args, format );
            if (isEnabled(LogLevel::error)) {
                Logger::write(LogLevel::error, _category, format, args);
            }
            va_end( args );
        #endif
    }
    
    void Loggable::dump(const char* msg, const uint8_t* buffer, uint16_t bufferLen, uint8_t wrapAt) {
        #if(LOGGING_ENABLED > 0)
            if (isEnabled(LogLevel::trace)) {
                Logger::dump(msg, buffer, bufferLen, wrapAt);
            }
        #endif
    }

    void Loggable::entry() {
        #if(LOGGING_ENABLED > 0) 
            if (isEnabled(LogLevel::trace)) {
                Logger::write(LogLevel::trace, _category, "entry.");
            }
        #endif
    }

    void Loggable::leave() {
        #if(LOGGING_ENABLED > 0) 
            if (isEnabled(LogLevel::trace)) {
                Logger::write(LogLevel::trace, _category, "leave.");
            }
        #endif
    }
}
