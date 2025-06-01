#ifndef __LoggerSink_h__
#define __LoggerSink_h__

#include <Arduino.h>

namespace ravensnight::logging {

    class LoggerSink {

        public:
            virtual void write(const char* line) = 0;
    };

}


#endif // __LoggerSink_h__