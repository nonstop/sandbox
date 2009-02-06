#include "local_logger.h"


void produceLogs(int ac, char* av[]) {
    LOG_INF << "Info string";
    LOG_WRN << "Warning string";
    LOG_DBG << "Debug string: ac=" << ac << ", av[0]=" << av[0];
    LOG_ERR << "Error string: " << "err text";
}

int main(int ac, char* av[]) {
    produceLogs(ac, av);
    LocalLogger::setLogLevel(LocalLogger::Warning);
    produceLogs(ac, av);
    return 0;
}

