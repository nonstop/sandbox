#include <iostream>
#include <stack>

using namespace std;

static bool matches(char l, char r)
{
    return (l == '[' && r == ']')
        || (l == '(' && r == ')')
        || (l == '{' && r == '}');
}

static void validate(const char* instr)
{
    std::stack<char> brkts;
    unsigned i = 0;
    for (char c = instr[0]; c != 0; ++i) {
        c = instr[i];
        if (c == '(' || c == '[' || c == '{') {
            brkts.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (brkts.empty() || !matches(brkts.top(), c)) {
                cout << instr << " - invalid: failed at " << i << endl;
                return;
            }
            brkts.pop();
        }
    }
    if (brkts.empty()) {
        cout << instr << " - valid" << endl;
    } else {
        cout << instr << " - invalid: " << brkts.size() << " not match" << endl;
    }
}

int main(int ac, char* av[])
{
    for (int i = 1; i < ac; ++i) {
        validate(av[i]);
    }
    return 0;
}
