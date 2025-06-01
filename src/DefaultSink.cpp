#include <DefaultSink.h>

namespace ravensnight::logging {

DefaultSink::DefaultSink(Print* print) {
    _out = print;
}

void DefaultSink::write(const char* logline) {
    _out->println(logline);
}

}