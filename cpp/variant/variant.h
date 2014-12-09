#ifndef SANDBOX_VARIANT_H
#define SANDBOX_VARIANT_H

#include <iostream>

using std::cout;
using std::endl;

#define TRACE(x) cout << __FILE__ << ':' << __LINE__ << ' ' << x << endl;

#include <stdexcept>
#include <vector>
#include <functional>

namespace details
{

template<typename T>
constexpr unsigned maxSize(unsigned sz) {
    return sizeof(T) < sz ? sz : sizeof(T);
}
template<typename First, typename Second, typename...Rest>
constexpr unsigned maxSize(unsigned sz) {
    return maxSize<Second, Rest...>(sizeof(First) < sz ? sz : sizeof(First));
}

template<typename T>
void validateTypes()
{
    static_assert(std::is_object<T>::value && !std::is_pointer<T>::value, "Pointers, references, void are not allowed");
}
template<typename First, typename Second, typename...Rest>
void validateTypes()
{
    static_assert(std::is_object<First>::value && !std::is_pointer<First>::value, "Pointers, references, void are not allowed");
    validateTypes<Second, Rest...>();
}

template<typename T, typename...Rest>
struct TypeFromList
{
    static const unsigned num = 1;
};

template<typename T, typename First, typename...Rest>
struct TypeFromList<T, First, Rest...>
{
    static const unsigned num = 1 + TypeFromList<T, Rest...>::num;
};
template<typename T, typename...Rest>
struct TypeFromList<T, T, Rest...>
{
    static const unsigned num = 1;
};

struct BasicDestr
{
    virtual void copyConstr(void* dst, const void* src) const = 0;
    virtual void destroy(void* p) const = 0;
};

template<typename T>
struct Destr : public BasicDestr
{
    virtual void copyConstr(void* dst, const void* src) const {
        new (dst) T(*reinterpret_cast<const T*>(src));
    }
    virtual void destroy(void* p) const {
        reinterpret_cast<T*>(p)->~T();
    }
};

struct BasicComparator
{
    virtual bool equals(const void* lhs, const void* rhs) const = 0;
};

template<typename T>
struct Comparator : public BasicComparator
{
    virtual bool equals(const void* lhsp, const void* rhsp) const {
        const T& lhs(*reinterpret_cast<const T*>(lhsp));
        const T& rhs(*reinterpret_cast<const T*>(rhsp));
        return lhs == rhs;
    }
};

template<typename First>
void addDestructor(std::vector<BasicDestr*>& ds)
{
    ds.push_back(new Destr<First>);
}

template<typename First, typename Second, typename...Rest>
void addDestructor(std::vector<BasicDestr*>& ds)
{
    ds.push_back(new Destr<First>);
    addDestructor<Second, Rest...>(ds);
}

template<typename T, typename...Rest>
std::vector<BasicDestr*> setupDestructors()
{
    std::vector<BasicDestr*> v;
    addDestructor<T, Rest...>(v);
    return v;
}

template<typename First>
void addComparator(std::vector<BasicComparator*>& ds)
{
    ds.push_back(new Comparator<First>);
}

template<typename First, typename Second, typename...Rest>
void addComparator(std::vector<BasicComparator*>& ds)
{
    ds.push_back(new Comparator<First>);
    addComparator<Second, Rest...>(ds);
}

template<typename T, typename...Rest>
std::vector<BasicComparator*> setupComparators()
{
    std::vector<BasicComparator*> v;
    addComparator<T, Rest...>(v);
    return v;
}
} // details

template<typename First, typename Second, typename...Rest>
class Variant;
template<typename First, typename Second, typename...Rest>
bool operator==(const Variant<First, Second, Rest...>& lhs, const Variant<First, Second, Rest...>& rhs);

template<typename First, typename Second, typename...Rest>
class Variant
{
public:
    template<typename T>
    explicit Variant(const T& v)
        : tag_(details::TypeFromList<T, First, Second, Rest...>::num - 1)
    {
        static_assert(details::TypeFromList<T, First, Second, Rest...>::num <= (2 + sizeof...(Rest)), "Type not in list");
        new (addr()) T(v);
    }
    const Variant(const Variant& that) {
        tag_ = that.tag_;
        desc().copyConstr(addr(), that.addr());
    }
    ~Variant() {
        destroy();
        details::validateTypes<First, Second, Rest...>();
    }
    const Variant& operator=(const Variant& that) {
        if (tag_ == that.tag_) {
            desc().copyConstr(addr(), that.addr());
        } else {
            destroy();
            tag_ = that.tag_;
            desc().copyConstr(addr(), that.addr());
        }
        return *this;
    }

    unsigned tag() const {
        return tag_;
    }
    template<typename T>
    const T& get() const {
        static_assert(details::TypeFromList<T, First, Second, Rest...>::num <= (2 + sizeof...(Rest)), "Type not in list");
        const unsigned tag = (details::TypeFromList<T, First, Second, Rest...>::num - 1);
        if (tag == tag_) {
            return *reinterpret_cast<const T*>(addr());
        }
        throw std::logic_error("Invalid type in variant.");
    }

    //template<typename First1, typename Second1, typename...Rest1>
    //friend
    //bool operator==(const Variant<First1, Second1, Rest1...>& lhs, const Variant<First1, Second1, Rest1...>& rhs);
    friend
    bool operator== <> (const Variant<First, Second, Rest...>& lhs, const Variant<First, Second, Rest...>& rhs);

private:
    inline void* addr() const {
        return (void*)buf_;
    }
    void destroy() {
        desc().destroy(addr());
    }
    const details::BasicDestr& desc() const {
        // FIXME vector -> array with smart ptrs
        static const std::vector<details::BasicDestr*> ds = details::setupDestructors<First, Second, Rest...>();
        return *ds[tag_];
    }

    unsigned tag_;
    char buf_[details::maxSize<Second, Rest...>(sizeof(First))];
};

template<typename First, typename Second, typename...Rest>
bool operator==(const Variant<First, Second, Rest...>& lhs, const Variant<First, Second, Rest...>& rhs)
{
    static const std::vector<details::BasicComparator*> ds = details::setupComparators<First, Second, Rest...>();
    if (lhs.tag_ == rhs.tag_) {
        return ds[lhs.tag_]->equals(lhs.addr(), rhs.addr());
    }
    return false;
}

#endif /* SANDBOX_VARIANT_H */

