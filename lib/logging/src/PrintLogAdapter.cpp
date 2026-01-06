#include <PrintLogAdapter.h>

namespace ravensnight::logging
{
    PrintLogAdapter::PrintLogAdapter(Print *print) {
        _out = print;
    }

    void PrintLogAdapter::out(const char *logline) {
        _out->println(logline);
    }
}