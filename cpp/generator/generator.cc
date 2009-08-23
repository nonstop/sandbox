#include <string>
#include <iostream>
#include <fstream>
#include <boost/foreach.hpp>
#include <boost/function.hpp>

#if 0
#define DEBUG(msg) std::cerr << __FILE__ << ":" << __LINE__ << " " << (msg) << std:: endl;
#else
#define DEBUG(msg) ;
#endif // 0

template<typename GeneratorTraits>
class generator
{
public:
    struct iterator {
        typedef std::forward_iterator_tag iterator_category;
        typedef typename GeneratorTraits::value_type value_type;
        typedef ptrdiff_t difference_type;
        typedef typename GeneratorTraits::value_type* pointer;
        typedef typename GeneratorTraits::value_type& reference;
        bool operator==(const iterator& it) {
            return this->endFlag_ == it.endFlag_;
        }
        bool operator!=(const iterator& it) {
            return !(*this == it);
        }
        iterator& operator++() {
            DEBUG(__FUNCTION__);
            value_ = traits_.yield();
            endFlag_ = traits_.end();
            return *this;
        }
        reference operator*() {
            DEBUG(__FUNCTION__);
            return value_;
        }
        iterator(GeneratorTraits& traits, bool endFlag = false)
            : traits_(traits), endFlag_(endFlag)
        {}
    private:
        typename GeneratorTraits::value_type value_;
        GeneratorTraits& traits_;
        bool endFlag_;
    };
    iterator begin() {
        DEBUG(__FUNCTION__);
        iterator it(traits_);
        return (++it);
    }
    iterator end() {
        DEBUG(__FUNCTION__);
        return iterator(traits_, true);
    }
    typedef iterator const_iterator;
private:
    GeneratorTraits traits_;
};

struct TextFileReaderTraits
{
    typedef std::string value_type;
    TextFileReaderTraits()
        : file_("generator.cc")
    {
        DEBUG(__FUNCTION__);
    }
    value_type yield()
    {
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
typedef generator<TextFileReaderTraits> text_file_reader;

int main()
{
    text_file_reader lineReader;

    size_t i = 0;
    BOOST_FOREACH(const std::string& line, lineReader) {
        std::cout << (++i) << "\t " << line << std::endl;
    }
    return 0;
}

