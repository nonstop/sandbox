#include <iostream>
#include <stdlib.h>

using namespace std;

static int reverseNum(int n)
{
    int newNum(0);
    while (n) {
        newNum *= 10;
        newNum += n  % 10;
        n /= 10;
    }
    return newNum;
}

int main(int ac, char* av[])
{
    for (int i = 1; i < ac; ++i) {
        cout << av[i] << " -> " << reverseNum(atoi(av[i])) << endl;
    }
    return 0;
}
