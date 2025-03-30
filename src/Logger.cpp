#include "Logger.h"

using namespace LOGGING;

Logger::Logger() {    
    this->_output = 0;    
}

void Logger::attach(Print* output) {
    Logger::_output = output;
}

void Logger::setLevel(LogLevel level) {
    Logger::_currentLevel = level;
}

void Logger::debug(const char* format, ...) {
    if (isEnabled(LogLevel::debug)) {
        va_list args;
        va_start( args, format );
        write("debug", format, args);
        va_end( args );
    }
}

void Logger::info(const char* format, ...) {
    if (isEnabled(LogLevel::info)) {
        va_list args;
        va_start( args, format );
        write("info", format, args);
        va_end( args );
    }    
}

void Logger::warn(const char* format, ...) {
    if (isEnabled(LogLevel::warn)) {
        va_list args;
        va_start( args, format );
        write("warn", format, args);
        va_end( args );
    }    
}

void Logger::error(const char* format, ...) {
    if (isEnabled(LogLevel::error)) {
        va_list args;
        va_start( args, format );
        write("error", format, args);
        va_end( args );
    }
}

void Logger::write(const char* prefix, const char* format, va_list& args) {
#if(LOGGING_ENABLED > 0)
    // nothing to write to
    if (_output == 0) return; 

    char buffer[512] = { 0 };
    vsprintf(buffer, format, args);

    _output->print(buffer);
    _output->print('\n');
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
    uint8_t count = 0;
    if (_output == 0) return;

    if (isEnabled(LogLevel::debug)) {
        _output->printf("[debug] %s (length=%d)\n", msg, len);

        count = 0;
        for (uint16_t i = 0; i < len; i++) {
            if ((wrapAt > 0) && (count == 0)) {
                _output->printf("%04X: ", i / wrapAt);
            }

            _output->printf("%02X ", buffer[i]);

            if (wrapAt > 0) {
                count++;
            
                if (count == wrapAt) {
                    _output->printf("\n");
                    count = 0;
                }
            }
        }
 
        _output->println();
    }    
#endif
}


// define the global serial logger
LogLevel Logger::_currentLevel = LogLevel::debug;
Print* Logger::_output = 0;
