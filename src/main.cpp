#include <Arduino.h>

#include <SerialLogAdapter.h>
#include <Logger.h>

using namespace ravensnight::logging;

SerialLogAdapter logAdapter;
#define BUFLEN 64

void setup() {
    Logger::setup(&logAdapter);
}

void loop() {
    uint8_t buffer[BUFLEN] = { 0 };

    for (int i = 0; i < BUFLEN; i++) {
        Logger::root.debug("Fill array at %d with %x", i, i);
        buffer[i] = i;
    }

    Logger::root.dump("Whole buffer:", buffer, BUFLEN, 8);

    delay(1000);
}
