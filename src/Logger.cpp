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

void Logger::log(LogLevel level, const char* format, ...) {
#if(LOGGING_ENABLED > 0)
    #ifdef _GLIBCXX_HAS_GTHREADS
    const std::lock_guard<std::mutex> lock(_mutex);
    #endif 

    if (isEnabled(level)) {
        va_list args;
        va_start( args, format );
        write(level, format, args);
        va_end( args );
    }
#endif // (LOGGING_ENABLED > 0)
}

void Logger::write(LogLevel level, const char* format, ...) {
    if (_output == 0) {
        return;
    };
    
    const char* prefix = Logger::_prefixes[(uint8_t)level];

    va_list args;
    va_start( args, format );

    strcpy(_logLine, prefix);
    vsprintf(_logLine + strlen(prefix), format, args);

    _output->println(_logLine);    

    va_end( args );
}

void Logger::debug(const char* format, ...) {
#if(LOGGING_ENABLED > 0)
    va_list args;
    va_start( args, format );
    log(LogLevel::debug, format, args);
    va_end( args );
#endif
}

void Logger::info(const char* format, ...) {
#if(LOGGING_ENABLED > 0)
    va_list args;
    va_start( args, format );
    log(LogLevel::info, format, args);
    va_end( args );
#endif
}

void Logger::warn(const char* format, ...) {
#if(LOGGING_ENABLED > 0)
    va_list args;
    va_start( args, format );
    log(LogLevel::warn, format, args);
    va_end( args );
#endif
}

void Logger::error(const char* format, ...) {
#if(LOGGING_ENABLED > 0)
    va_list args;
    va_start( args, format );
    log(LogLevel::error, format, args);
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

    if ((_output == 0) || (!isEnabled(LogLevel::debug))) {
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
    sprintf(_logLine, "[debug] %s (length=%d)", msg, len);
    _output->println(_logLine);

    // print bytes
    count = 0;
    for (uint16_t i = 0; i < len; i++) {

        // print line number
        if (count == 0) {
            sprintf(_logLine, "%04X: ", i / wrap);
        }

        // print block
        sprintf(_logLine + (LOGBUFFER_DUMP_OFFSET + (count * 3)), "%02X ", buffer[i]);            
        count++;            

        if (count == wrap) {
            _output->println(_logLine);
            count = 0;
        }
    }

    if (count > 0) {
        _output->println(_logLine);
    }
#endif
}

// define the global serial logger
LogLevel Logger::_rootLevel = LogLevel::debug;
LoggerSink* Logger::_output = 0;

#if (LOGGING_ENABLED > 0)
char* Logger::_logLine = (char*)malloc(LOGBUFFER_SIZE);
const char* Logger::_prefixes[LOGLEVEL_COUNT] = {
    "[trace] ",
    "[debug] ",
    "[info] ",
    "[warn] ",
    "[error] "
};
#endif

#ifdef _GLIBCXX_HAS_GTHREADS
std::mutex Logger::_mutex;
#endif 

}