#ifndef __DefaultSink_h__
#define __DefaultSink_h__


#include <LoggerSink.h>
#include <Print.h>

namespace ravensnight::logging {

    class DefaultSink : public LoggerSink {

        private:
            Print* _out;

        public:

            DefaultSink(Print *printer);
            void out(const char* text);
    };


}


#endif // __DefaultSink_h__