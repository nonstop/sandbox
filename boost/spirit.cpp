#include <iostream>
#include <sstream>
#include <string>

#include <boost/spirit/include/classic_grammar_def.hpp>

using namespace std;

/**
 * text presentation
 * Foo {%d; %s}
 * */

struct Foo {
    int f1;
    string f2;
    bool operator==(const Foo& f) {
        return f1 == f.f1 && f2 == f.f2;
    }
};

template<typename Stream>
Stream& operator<<(Stream& str, const Foo& f) {
    str << "Foo {" << f.f1 << "; \"" << f.f2 << "\"}";
    return str;
}

int main() {
    Foo f;
    f.f1 = 25;
    f.f2 = "foo text25";
    stringstream str;
    str << f;
    cout << f << endl;


    return 0;
}

