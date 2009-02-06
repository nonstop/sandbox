#include <iostream>

#include "local_logger.h"

using std::cout;
using std::endl;

LocalLogger::LogLevel LocalLogger::currentLogLevel_ = LocalLogger::Debug;

void LocalLogger::setLogLevel(LogLevel ll) {
    LocalLogger::currentLogLevel_ = ll;
}

LocalLogger::LocalLogger(LogLevel ll, const char* file, int line)
    : ll_(ll), file_(file), line_(line)
{
    if (ll_ <= currentLogLevel_)
        msg_ << file_ << ":" << line_ << " ";
}

LocalLogger::~LocalLogger()
{
    if (ll_ <= currentLogLevel_)
        cout << msg_.str() << endl;
}

