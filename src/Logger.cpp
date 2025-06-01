#include <Logger.h>

namespace ravensnight::logging {

Logger::Logger() {    
    this->_output = 0;    
}

void Logger::attach(LoggerSink* output) {
    Logger::_output = output;
}

void Logger::setLevel(LogLevel level) {
    Logger::_currentLevel = level;
}

void Logger::debug(const char* format, ...) {
#if(LOGGING_ENABLED > 0)

    #ifdef _GLIBCXX_HAS_GTHREADS
    const std::lock_guard<std::mutex> lock(_mutex);
    #endif 

    if (isEnabled(LogLevel::debug)) {
        va_list args;
        va_start( args, format );
        write("[debug] ", format, args);
        va_end( args );
    }
#endif
}

void Logger::info(const char* format, ...) {
#if(LOGGING_ENABLED > 0)
    #ifdef _GLIBCXX_HAS_GTHREADS
    const std::lock_guard<std::mutex> lock(_mutex);
    #endif 

    if (isEnabled(LogLevel::info)) {
        va_list args;
        va_start( args, format );
        write("[info] ", format, args);
        va_end( args );
    }    
#endif
}

void Logger::warn(const char* format, ...) {
#if(LOGGING_ENABLED > 0)
    #ifdef _GLIBCXX_HAS_GTHREADS
    const std::lock_guard<std::mutex> lock(_mutex);
    #endif 

    if (isEnabled(LogLevel::warn)) {
        va_list args;
        va_start( args, format );
        write("[warn] ", format, args);
        va_end( args );
    }    
#endif
}

void Logger::error(const char* format, ...) {
#if(LOGGING_ENABLED > 0)
    #ifdef _GLIBCXX_HAS_GTHREADS
    const std::lock_guard<std::mutex> lock(_mutex);
    #endif 

    if (isEnabled(LogLevel::error)) {
        va_list args;
        va_start( args, format );
        write("[error] ", format, args);
        va_end( args );
    }
#endif
}

void Logger::write(const char* prefix, const char* format, va_list& args) {
#if(LOGGING_ENABLED > 0)
    // nothing to write to
    if (_output == 0) return; 

    strcpy(_logLine, prefix);
    vsprintf(_logLine + strlen(prefix), format, args);

    _output->write(_logLine);    
#endif
}

bool Logger::isEnabled(LogLevel level) {
#if(LOGGING_ENABLED > 0)
    return (level <= _currentLevel);
#else
    return false;
#endif
}

void Logger::dump(const char* msg, const uint8_t* buffer, uint16_t len, uint8_t wrapAt) {
#if(LOGGING_ENABLED > 0)
    #ifdef _GLIBCXX_HAS_GTHREADS
    const std::lock_guard<std::mutex> lock(_mutex);
    #endif 

    uint8_t count = 0;
    uint8_t wrap = wrapAt > 0 ? wrapAt : LOGBUFFER_SIZE - 1;
    uint8_t offset = wrapAt > 0 ? 5 : 0;
    if (_output == 0) return;

    if (isEnabled(LogLevel::debug)) {
        sprintf(_logLine, "[debug] %s (length=%d)", msg, len);
        _output->write(_logLine);

        count = 0;

        for (uint16_t i = 0; i < len; i++) {
            if ((wrapAt > 0) && (count == 0)) {
                sprintf(_logLine, "%04X: ", i / wrapAt);
            }

            sprintf(_logLine + (offset + (i * 3)), "%02X ", buffer[i]);            
            count++;            

            if (count == wrap) {
                _output->write(_logLine);
                count = 0;
            }
        }
 
        if (count > 0) {
            _output->write(_logLine);
        }
    }    
#endif
}

// define the global serial logger
LogLevel Logger::_currentLevel = LogLevel::debug;
LoggerSink* Logger::_output = 0;
char* Logger::_logLine = (char*)malloc(LOGBUFFER_SIZE);

#ifdef _GLIBCXX_HAS_GTHREADS
std::mutex Logger::_mutex;
#endif 

}