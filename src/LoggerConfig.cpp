#include <Logger.h>

namespace ravensnight::logging {
    LogLevel getLogLevel(const char* category) {
        return LogLevel::trace;
    }
}