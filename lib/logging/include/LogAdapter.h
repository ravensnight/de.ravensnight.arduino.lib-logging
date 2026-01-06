#ifndef __LogAdapter_h__
#define __LogAdapter_h__

#include <Arduino.h>

namespace ravensnight::logging {

    class LogAdapter {

        public:

            /**
             * Write a line
             */
            virtual void out(const char* text) = 0;

    };

}


#endif // __LogAdapter_h__