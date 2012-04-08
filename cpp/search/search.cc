#include <stdlib.h>
#include <string>
#include <iostream>
#include <queue>

static size_t search(const std::string& str, const size_t k, char c)
{
    size_t len = 0;
    std::queue<size_t> indexes;
    size_t pos = str.find(c);
    while (pos != std::string::npos) {
        if (indexes.size() < k) {
            indexes.push(pos);
            len = pos - indexes.front();
        } else {
            indexes.pop();
            indexes.push(pos);
            const size_t d = pos - indexes.front();
            len = d < len ? d : len;
        }
        pos = str.find(c, pos + 1);
    }
    return indexes.size() < k ? 0 : len + 1;
}

int main(int ac, char* av[])
{
    if (ac < 3) {
        return 1;
    }
    std::cout << search(av[2], atoi(av[1]), '1') << std::endl;
    return 0;
}
