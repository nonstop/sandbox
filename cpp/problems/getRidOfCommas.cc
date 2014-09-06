#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

static void getRidOfCommas(char* out, const char* instr)
{
    unsigned i(0);
    char c = instr[i];
    unsigned commasCnt(0);
    while (c) {
        c = instr[i];
        if (c == ',') {
            ++commasCnt;
        } else {
            out[i - commasCnt] = c;
        }
        ++i;
    }
    out[i - commasCnt] = 0;
    cout << instr << " -> " << out << endl;
}

int main(int ac, char* av[])
{
    for (int i = 1; i < ac; ++i) {
        vector<char> buff(strlen(av[i]) + 1, 0);
        getRidOfCommas(&buff[0], av[i]);
    }
    return 0;
}
