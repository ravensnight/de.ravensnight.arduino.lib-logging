#include <Logger.h>

namespace ravensnight::logging {

Logger::Logger() {    
    this->_output = 0;    
}

void Logger::attach(LoggerSink* output) {
    Logger::_output = output;
}

void Logger::setLevel(LogLevel level) {
    Logger::_rootLevel = level;
}

void Logger::write(LogLevel level, const char* category, const char* format, va_list* args) {    
    #if (LOGGING_ENABLED > 0)
        #ifdef _GLIBCXX_HAS_GTHREADS
        const std::lock_guard<std::mutex> lock(_mutex);
        #endif 

        if (_output == 0) {
            return;
        };
        
        const char* prefix = Logger::_prefixes[(uint8_t)level];
        const char* cat = category == 0 ? "RootLogger" : category;

        sprintf(_logLine, "[%s::%s] ", cat, prefix);

        if (args == 0) {
            sprintf(_logLine + strlen(_logLine), format);
        } else {
            vsprintf(_logLine + strlen(_logLine), format, *args);
        }
        _output->out(_logLine);

    #endif
}

void Logger::trace(const char* format, ...) {
#if(LOGGING_ENABLED > 0)
    va_list args;
    va_start( args, format );
    write(LogLevel::trace, 0, format, &args);
    va_end( args );
#endif
}

void Logger::debug(const char* format, ...) {
#if(LOGGING_ENABLED > 0)
    va_list args;
    va_start( args, format );
    write(LogLevel::debug, 0, format, &args);
    va_end( args );
#endif
}

void Logger::info(const char* format, ...) {
#if(LOGGING_ENABLED > 0)
    va_list args;
    va_start( args, format );
    write(LogLevel::info, 0, format, &args);
    va_end( args );
#endif
}

void Logger::warn(const char* format, ...) {
#if(LOGGING_ENABLED > 0)
    va_list args;
    va_start( args, format );
    write(LogLevel::warn, 0, format, &args);
    va_end( args );
#endif
}

void Logger::error(const char* format, ...) {
#if(LOGGING_ENABLED > 0)
    va_list args;
    va_start( args, format );
    write(LogLevel::error, 0, format, &args);
    va_end( args );
#endif
}

bool Logger::isEnabled(LogLevel level) {
#if(LOGGING_ENABLED > 0)
    return (level <= _rootLevel);
#else
    return false;
#endif
}

void Logger::dump(const char* msg, const uint8_t* buffer, uint16_t len, uint8_t wrapAt) {
#if(LOGGING_ENABLED > 0)
    #ifdef _GLIBCXX_HAS_GTHREADS
    const std::lock_guard<std::mutex> lock(_mutex);
    #endif 

    if ((_output == 0) || (!isEnabled(LogLevel::trace))) {
        return;
    }

    uint8_t count = 0;
    uint8_t wrap = wrapAt;

    // prepare length
    if (wrap > 0) {
        if (wrap > (LOGBUFFER_SIZE - (1 + LOGBUFFER_DUMP_OFFSET))) {
            wrap = (LOGBUFFER_SIZE - (1 + LOGBUFFER_DUMP_OFFSET));
        }
    } else {
        wrap = LOGBUFFER_SIZE - (1 + LOGBUFFER_DUMP_OFFSET);
    }

    // print first line
    sprintf(_logLine, "[dump] %s (length: %d):", msg, len);
    _output->out(_logLine);

    // print bytes
    count = 0;
    char* ptr = _logLine;
    for (uint16_t i = 0; i < len; i++) {

        // print line number
        if (count == 0) {
            sprintf(ptr, "%04X: ", i / wrap);
            ptr += 6;
        }

        // print block
        sprintf(ptr, "%02X ", buffer[i]);
        ptr += 3;
        count++;            

        if (count == wrap) {
            _output->out(ptr);
            ptr = _logLine;
            count = 0;
        }
    }

    if (count > 0) {
        _output->out(ptr);        
    }
#endif
}

// define the global serial logger
LogLevel Logger::_rootLevel = LogLevel::debug;
LoggerSink* Logger::_output = 0;
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

#ifdef _GLIBCXX_HAS_GTHREADS
std::mutex Logger::_mutex;
#endif 

}