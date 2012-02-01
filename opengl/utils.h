#ifndef GIEL_UTILS_H
#define GIEL_UTILS_H

#include <stdio.h>

#define TRACE(fmt, ...) fprintf(stderr, "%s:%d " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)


#endif /* GIEL_UTILS_H */

