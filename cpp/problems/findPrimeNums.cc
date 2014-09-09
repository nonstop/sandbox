#include <iostream>
#include <vector>
#include <limits>
#include <stdlib.h>

using namespace std;

static void findPrimeNums(int n)
{
    if (n < 2) {
        return;
    } else if (n == 2) {
        cout << "prime nums before 2 are: 1" << endl;
        return;
    }
    cout << "prime nums before " << n << " are:";
    vector<bool> allints(n, true);
    for (int i = 2; i < n; ++i) {
        if (allints[i]) {
            cout << ' ' << i;
        }
        for (int j = i + i; j < n; j = j + i) {
            allints[j] = false;
        }
    }
    cout << endl;
}

int main(int ac, char* av[])
{
    for (int i = 1; i < ac; ++i) {
        findPrimeNums(atoi(av[i]));
    }
    return 0;
}
