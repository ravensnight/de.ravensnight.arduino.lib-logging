#ifndef __LoggerSink_h__
#define __LoggerSink_h__

#include <Arduino.h>

namespace LOGGING {

    class LoggerSink {

        public:
            virtual void write(const char* line) = 0;
    };

}


#endif // __LoggerSink_h__