#include <iostream>
#include <utility>

using namespace std;

std::pair<char, size_t> findLongRun(const char* instr)
{
    pair<char, size_t> res(instr[0], 1);
    unsigned i = 0;
    char currentRunChar = 0;
    size_t currentRunLength = 0;
    for (char c = instr[0]; c != 0; ++i) {
        c = instr[i];
        if (c == currentRunChar) {
            ++currentRunLength;
            continue;
        }
        if (currentRunLength > res.second) {
            res.first = currentRunChar;
            res.second = currentRunLength;
        }
        currentRunChar = c;
        currentRunLength = 1;
    }
    if (currentRunLength > res.second) {
        res.first = currentRunChar;
        res.second = currentRunLength;
    }
    return res;
}

int main(int ac, char* av[])
{
    for (int i = 1; i < ac; ++i) {
        std::pair<char, size_t> res(findLongRun(av[i]));
        cout << std::string(res.second, res.first) << endl;
    }
    return 0;
}
