#include <iostream>

using namespace std;

enum State {None, InsideComment};

void printStr(const char* instr)
{
    State st = None;
    unsigned i = 0;
    for (char c = instr[0]; c != 0; ++i) {
        c = instr[i];
        switch (st) {
        case None: {
            if (c == '/' && instr[i + 1] == '*') {
                st = InsideComment;
                ++i;
                continue;
            }
            break;
        }
        case InsideComment: {
            if (c == '*' && instr[i + 1] == '/') {
                st = None;
                ++i;
            }
            continue;
        }
        }
        cout << c;
    }
    cout << '\n';
}

int main(int ac, char* av[])
{
    for (int i = 1; i < ac; ++i) {\
        printStr(av[i]);
    }
    return 0;
}

