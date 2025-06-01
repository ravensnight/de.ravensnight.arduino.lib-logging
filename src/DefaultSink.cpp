#include <DefaultSink.h>

using namespace LOGGING;

DefaultSink::DefaultSink(Print* print) {
    _out = print;
}

void DefaultSink::write(const char* logline) {
    _out->println(logline);
}
