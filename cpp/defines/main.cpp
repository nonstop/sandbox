#include <unistd.h>
#include <time.h>
/*
#include <stdio.h>

#define OWNER "NONSTOP"

#define STDFMT "%d %s %d %s:%d "
#define STD getpid(), OWNER, time(NULL), __FILE__, __LINE__
#define debug(format, ...) fprintf(stderr, STDFMT # format, STD, ## __VA_ARGS__); fprintf(stderr, "\n")

int main(int ac, char *av[])
{
    debug("first string");
    sleep(1);
    debug("%dnd %s", 2, "string");
    return 0;
}
*/

#include <iostream>
#include <boost/format.hpp>

#define OWNER "NONSTOP"

const std::string STDFMT="%d %s %d %s:%d ";
#define STD getpid() % OWNER % time(NULL) % __FILE__ % __LINE__
#define debug(formatStr, values) std::cout << boost::format(STDFMT + formatStr) % STD % values << std::endl


int main(int ac, char *av[])
{
    debug("%s", "first string");
    sleep(1);
    debug("%snd %s", 2 % "string");
    return 0;
}

