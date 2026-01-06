#ifndef __PrintLogAdapter_h__
#define __PrintLogAdapter_h__

#include <LogAdapter.h>
#include <Print.h>

namespace ravensnight::logging {

    class PrintLogAdapter : public LogAdapter {

        private:
            Print* _out;

        public:

            PrintLogAdapter(Print *printer);
            void out(const char* text);
    };


}


#endif // __PrintLogAdapter_h__