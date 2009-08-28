#ifndef GENERATOR_H
#define GENERATOR_H

#if 0
#define DEBUG(msg) std::cerr << __FILE__ << ":" << __LINE__ << " " << (msg) << std:: endl;
#else
#define DEBUG(msg) ;
#endif // 0

template<typename GeneratorTraits>
class generator
{
public:
    generator(typename GeneratorTraits::init_type val) : traits_(val) {}
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

#endif /* GENERATOR_H */

