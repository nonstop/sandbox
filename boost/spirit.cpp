#include <iostream>
#include <sstream>
#include <string>

#include <boost/bind.hpp>
#include <boost/spirit.hpp>

using namespace std;
using namespace boost::spirit;

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

struct foo_grammar : public grammar<foo_grammar> {
    template<typename ScannerT>
    struct definition {
        rule<ScannerT> integer_literal;
        rule<ScannerT> string_literal;
        rule<ScannerT> record_list;
        rule<ScannerT> record;
        definition(const foo_grammar& self) {
            string_literal = lexeme_d[
				ch_p('"') >>
				*(
					(anychar_p - ch_p('"') )  |
					str_p("\\\"")
				) >>
				ch_p('"')
			];

            record_list = record >> *(ch_p(',') >> record);
            record = str_p("Foo {")
                >> int_p >> *(ch_p(';'))
                >> string_literal[boost::bind(&foo_grammar::do_f2, &self, _1, _2)] >> ch_p('}');
        }
		rule<ScannerT> const& start() {
            return record_list;
        }
    };
    void do_f2(const char* beg, const char* end) const {
        cout << "do_f2 beg=" << *beg << " end=" << *end << endl;
        string str(beg, end - beg);
        cout << "str=" << str << endl;
    }
};

int main() {
    Foo f;
    f.f1 = 25;
    f.f2 = "foo text25";
    stringstream str;
    str << f;
    cout << f << endl;

    foo_grammar g;
	parse_info<> info = parse(str.str().c_str(), g, space_p);
	if(!info.full){
		cout << "Error found at location: " << info.stop << endl;
	}else{
		cout << "Success!" << endl;
	}


    return 0;
}

