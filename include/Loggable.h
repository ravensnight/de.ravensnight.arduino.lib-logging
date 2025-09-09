#ifndef __Loggable_h__
#define __Loggable_h__

#include <Arduino.h>

#include <Logger.h>

namespace ravensnight::logging {

    extern LogLevel getLogLevel(const char* category);

    class Loggable {
        private:

            const char* _category;

        protected:

            Loggable(const char* category);

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