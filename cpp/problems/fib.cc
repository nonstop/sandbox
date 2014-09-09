#include <iostream>
#include <stdlib.h>

using namespace std;

void fib(int n)
{
    if (n == 0) {
        cout << '0' << endl;
    }
    if (n == 1) {
        cout << "0 1" << endl;
    }
    cout << "0 1";
    int prev1 = 1, prev2 = 0;
    for (int i = 2;; ++i) {
        int val(prev1 + prev2);
        if (val >=n) {
            break;
        }
        prev2 = prev1;
        prev1 = val;
        cout << ' ' << val;
    }
    cout << endl;
}

int main(int ac, char* av[])
{
    for (int i = 1; i < ac; ++i) {
        fib(atoi(av[i]));
    }
    return 0;
}
