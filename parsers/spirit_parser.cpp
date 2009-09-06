#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/spirit.hpp>

using namespace std;
using namespace boost::spirit;

struct Object {
    int m_num;
    string m_str;
    std::vector<int> m_arr;
    bool m_log;
    Object* m_obj;

    //bool operator==(const Foo& f) {
        //return f1 == f.f1 && f2 == f.f2;
    //}
};
typedef std::vector<Object> Objects;

template<typename Stream>
Stream& operator<<(Stream& str, const Object& obj) {
    str << " Object " << obj.m_num << " \"" << obj.m_str << "\""
        << " log" << obj.m_log << " [";
    BOOST_FOREACH(int i, obj.m_arr) {
        str << i << " ";
    }
    str << "]\n";
    if (obj.m_obj) {
        str << "\t" << *obj.m_obj;
    }
    return str;
}

struct foo_grammar : public grammar<foo_grammar> {
    foo_grammar(Objects& objs) : objs_(objs) {}
    template<typename ScannerT>
    struct definition {
        rule<ScannerT> special_literal;
        rule<ScannerT> array_literal;
        rule<ScannerT> number_literal;
        rule<ScannerT> string_literal;
        rule<ScannerT> key_literal;
        rule<ScannerT> value_literal;
        rule<ScannerT> key_value;
        rule<ScannerT> object_list;
        rule<ScannerT> object;
        definition(const foo_grammar& self) {
            special_literal = lexeme_d[str_p("true") | str_p("false") | str_p("null")];
            array_literal = str_p("[") >> *(value_literal >> *(ch_p(",") >> value_literal)) >> str_p("]");
            number_literal = digit_p;
            string_literal = lexeme_d[
                ch_p('"') >>
                *(
                    (anychar_p - ch_p('"') )  |
                    str_p("\\\"")
                ) >>
                ch_p('"')
            ];

            key_literal = ch_p('"')
                    >> lexeme_d[+(anychar_p - ch_p('"'))]
                        [boost::bind(&foo_grammar::do_key, &self, _1, _2)]
                    >> ch_p('"');

            value_literal = (special_literal | number_literal | string_literal)
                [boost::bind(&foo_grammar::do_value, &self, _1, _2)] | object | array_literal;

            key_value = key_literal >> str_p(":") >> value_literal;

            object = str_p("{") >> (key_value % ch_p(',')) >> str_p("}")
                [boost::bind(&foo_grammar::do_object, &self, _1, _2)];

            object_list = str_p("{") >> key_value >> str_p("}") >> end_p;
        }
        rule<ScannerT> const& start() {
            return object_list;
        }
    };
    void do_object(const char* beg, const char* end) const {
        cout << "****   object done   ****" << endl;
    }
    void do_key(const char* beg, const char* end) const {
        string str(beg, end - beg);
        cout << "key=" << str << endl;
    }
    void do_value(const char* beg, const char* end) const {
        string str(beg, end - beg);
        cout << "value=" << str << endl;
    }
private:
    Object obj_;
    Objects& objs_;
};

int main() {
    string objsStr;
    {
        ifstream objsFile("json.example", ifstream::in | ifstream::binary);
        while (objsFile.good()) {
            objsStr += objsFile.get();
        }
    }
    objsStr.resize(objsStr.size() - 1);
    cout << "<" << objsStr << ">" << endl;

    Objects objs;
    foo_grammar g(objs);
    parse_info<> info = parse(objsStr.c_str(), g, space_p);
    if(!info.full){
        cout << "Error found at location: " << info.stop << endl;
    }else{
        cout << "Success!" << endl;
        BOOST_FOREACH(const Object& obj, objs) {
            cout << obj << endl;
        }
    }


    return 0;
}


