#include <Arduino.h>

#include <Logger.h>
#include <DefaultSink.h>

using namespace ravensnight::logging;

DefaultSink logAdapter(&Serial);
#define BUFLEN 64

void setup() {
    #ifdef ESP32
    Serial.setDebugOutput(true);
    #endif
    Serial.begin(115200);

    Logger::attach(&logAdapter);
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
