#ifndef __SerialLogAdapter__
#define __SerialLogAdapter__

#include <Arduino.h>
#include <PrintLogAdapter.h>

namespace ravensnight::logging {

    class SerialLogAdapter : public PrintLogAdapter {

        private:

            HardwareSerial* _serial;

        public:

            SerialLogAdapter();
            SerialLogAdapter(unsigned long speed);
            SerialLogAdapter(HardwareSerial* serial, unsigned long speed);

            /** Configure the serial output */
            void setup(unsigned long speed);
    };
}

#endif // __SerialLogAdapter__