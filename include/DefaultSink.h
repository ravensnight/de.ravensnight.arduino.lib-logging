#ifndef __DefaultSink_h__
#define __DefaultSink_h__


#include <LoggerSink.h>
#include <Print.h>

namespace LOGGING {

    class DefaultSink : public LoggerSink {

        private:

            Print* _out;

        public:

            DefaultSink(Print *printer);
            void write(const char* line);
    };


}


#endif // __DefaultSink_h__