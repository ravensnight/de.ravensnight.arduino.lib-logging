#include "Logger.h"

using namespace LOGGING;

Logger::Logger(Print* output) {    
    this->_output = output;    
}

void Logger::setLevel(LogLevel level) {
    this->_currentLevel = level;
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
    uint8_t i = 0;
    char c = 0;
    boolean p = false;
    int d;
    double dbl;
    char* s;

    _output->printf("[%-5s] ", prefix);
    do {
        c = format[i];
        if (c == '\0') break;

        if (p) {
            switch (c) {
                case 'x':
                    d = va_arg(args, int);
                    _output->printf("%x", d);
                    break;

                case 's':
                    s = va_arg(args, char*);
                    _output->printf("%s", s);
                    break;

                case 'd':
                    d = va_arg(args, int);
                    _output->printf("%d", d);
                    break;

                case 'f':
                    dbl = va_arg(args, double);
                    _output->printf("%f", dbl);
                    break;

                default:
                    _output->print("%");
                    _output->print(c);
                    break;
            }

            p = false;
        } else {
            switch (c) {
                case '%':
                    p = true;
                    break;
                
                default:
                    _output->print(c);
                    break;
            }
        }

        i++;
    } while (true);
    
    _output->print('\n');
}

boolean Logger::isEnabled(LogLevel level) {
    return (level <= _currentLevel);
}

Logger& Logger::defaultLogger() {
    return _defaultLogger;
}

void Logger::dump(const char* msg, const uint8_t* buffer, uint16_t len, uint8_t wrapAt) {
    uint8_t count = 0;

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
}

// define the global serial logger
Logger Logger::_defaultLogger = Logger(&Serial);
