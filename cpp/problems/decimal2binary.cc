#include <iostream>
#include <stdlib.h>

using namespace std;

std::string toBinary(unsigned n)
{
    static const size_t LENGTH = sizeof(int) * 8;
    char buff[LENGTH + 1] = {};
    int i = 0;
    while (i < LENGTH) {
        buff[LENGTH - i - 1] = ((n & (1 << i)) ? '1' : '0');
        ++i;
    }
    return buff;
}

int main(int ac, char* av[])
{
    for (int i = 1; i < ac; ++i) {
        unsigned n = atoi(av[i]);
        cout << n << ' ' << toBinary(n) << endl;
    }
    return 0;
}
