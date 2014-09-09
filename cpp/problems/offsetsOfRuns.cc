#include <iostream>

using namespace std;

static void printOffsets(const char* instr)
{
    char prevChar = 0;
    unsigned length = 0;
    unsigned i = 0;
    while (char c = instr[i]) {
        if (c == prevChar) {
            ++length;
            if (length == 2) {
                cout << (i - 1);
            }
        } else {
            prevChar = c;
            length = 1;
        }
        ++i;
        c = instr[i];
    }
    cout << endl;
}

int main(int ac, char* av[])
{
    for (int i = 1; i < ac; ++i) {
        printOffsets(av[i]);
    }
    return 0;
}
