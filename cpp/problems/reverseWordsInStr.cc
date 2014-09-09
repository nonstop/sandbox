#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

typedef pair<size_t, size_t> token_t;
typedef vector<token_t> tokens_t;

static tokens_t tokenize(const char* instr)
{
    tokens_t tokens;
    token_t tok(0, 0);
    unsigned i(0);
    char c = instr[i];
    while (c) {
        c = instr[i];
        if (c == 0 || c == ' ') {
            tokens.push_back(tok);
            tok.first = i + 1;
            tok.second = 0;
        } else {
            ++tok.second;
        }
        ++i;
    }
    return tokens;
}

static std::string reverseStrWords(const char* instr)
{
    std::string s;
    const tokens_t tokens(tokenize(instr));
    for (tokens_t::const_reverse_iterator it = tokens.rbegin(), end = tokens.rend(); it != end; ++it) {
        if (!s.empty()) {
            s += ' ';
        }
        s += string(instr + it->first, it->second);
    }
    return s;
}

int main(int ac, char* av[])
{
    for (int i = 1; i < ac; ++i) {
        cout << '[' << av[i] << "] -> [" << reverseStrWords(av[i]) << ']' << endl;
    }
    return 0;
}
