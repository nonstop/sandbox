#include <iostream>
#include <string.h>

using namespace std;

static int atoi__(const char* instr)
{
    int sign = 1;
    int n(0);
    unsigned i(0);
    char c(instr[i]);
    while (c) {
        c = instr[i];
        if (c == 0) {
            return n * sign;
        }
        if (i == 0 && c == '-') {
            sign = -1;;
        } else if (c >= '0' && c <= '9') {
            n *= 10;
            n += (c - '0');
        } else {
            return 0;
        }
        ++i;
    }
    return n * sign;
}

int main(int ac, char* av[])
{
    for (int i = 1; i < ac; ++i) {
        cout << "str [" << av[i] << "] num [" << atoi__(av[i]) << ']' << endl;
    }
    return 0;
}
