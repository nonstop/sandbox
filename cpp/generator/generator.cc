#include <string>
#include <iostream>
#include <fstream>
#include <boost/foreach.hpp>
#include <boost/function.hpp>

#include "generator.h"

struct ReadFileByLine
{
    typedef const char* init_type;
    typedef std::string value_type;
    ReadFileByLine(init_type filename) : file_(filename) {
        DEBUG(__FUNCTION__);
    }
    value_type yield() {
        DEBUG(__FUNCTION__);
        value_type value_ = "";
        do {
            const char c = file_.get();
            if ((c == '\n') || (!file_.good())) {
                break;
            } else {
                value_ += c;
            }
        } while (1);
        return value_;
    }
    bool end() {
        DEBUG(__FUNCTION__);
        return !file_.good();
    }
private:
    std::ifstream file_;
};

int main()
{
    typedef generator<ReadFileByLine> file_reader;
    file_reader lineReader("generator.cc");

    size_t i = 0;
    BOOST_FOREACH(const std::string& line, lineReader) {
        std::cout << (++i) << "\t " << line << std::endl;
    }
    return 0;
}

