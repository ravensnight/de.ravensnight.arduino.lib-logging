#ifndef __LoggerSink_h__
#define __LoggerSink_h__

#include <Arduino.h>

namespace ravensnight::logging {

    class LoggerSink {

        public:

            /**
             * Write a line
             */
            virtual void out(const char* text) = 0;

    };

}


#endif // __LoggerSink_h__