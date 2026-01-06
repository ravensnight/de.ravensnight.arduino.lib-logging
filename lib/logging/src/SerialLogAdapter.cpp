#include <SerialLogAdapter.h>

namespace ravensnight::logging {

    SerialLogAdapter::SerialLogAdapter() : SerialLogAdapter(&Serial, 115200L) {
    }

    SerialLogAdapter::SerialLogAdapter(unsigned long speed) : SerialLogAdapter(&Serial, speed) {
    }

    SerialLogAdapter::SerialLogAdapter(HardwareSerial* serial, unsigned long speed) : PrintLogAdapter(serial) {
        _serial = serial;
        setup(speed);
    }
    
    void SerialLogAdapter::setup(unsigned long speed) {
        #ifdef ESP32
            _serial->setDebugOutput(true);
        #endif

        _serial->begin(speed);
    }
}