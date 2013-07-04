#include <iostream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#define TRACE(format, ...) \
fprintf(stderr, "%s:%d " format "\n", __FILE__, __LINE__, ## __VA_ARGS__)
#define TRACES(...) \
std::cerr << __FILE__ << ':' << __LINE__ << ' ' << __VA_ARGS__ << std::endl

class BigNumber;
std::ostream& operator<<(std::ostream& os, const BigNumber& n);

class BigNumber
{
public:
    BigNumber() {
        val_.push_back(0);
    }
    explicit BigNumber(const std::string& s) {
        for (size_t i = 0; i < s.size(); ++i) {
            assert(s[i] >= '0' && s[i] <= '9');
            val_.push_back(s[i] - '0');
        }
    }
    std::string toString() const {
        std::string s;
        for (size_t i = 0; i < val_.size(); ++i) {
            s += (val_[i] + '0');
        }
        return s;
    }
    bool operator==(const BigNumber& n) const {
        return val_ == n.val_;
    }
    bool operator!=(const BigNumber& n) const {
        return val_ != n.val_;
    }
    bool operator>(const BigNumber& n) const {
        if (val_.size() != n.val_.size()) {
            return val_.size() > n.val_.size();
        } else {
            return val_ > n.val_;
        }
    }
    bool operator<(const BigNumber& n) const {
        if (val_.size() != n.val_.size()) {
            return val_.size() < n.val_.size();
        } else {
            return val_ < n.val_;
        }
    }
    BigNumber operator+(const BigNumber& rhs) const {
        BigNumber n1, n2;
        if (*this > rhs) {
            n1 = *this;
            n2 = rhs;
        } else {
            n1 = rhs;
            n2 = *this;
        }
        std::vector<char> newVal(n1.val_);
        int j = 0;
        char overflow = 0;
        for (int i = n2.val_.size() - 1; i >= 0; --i, ++j) {
            const int idx = newVal.size() - 1 - j;
            newVal[idx] += n2.val_[i] + overflow;
            if (newVal[idx] > 9) {
                overflow = 1;
                newVal[idx] -= 10;
            } else {
                overflow = 0;
            }
        }
        while (overflow) {
            const int idx = newVal.size() - 1 - j;
            if (idx >= 0) {
                newVal[idx] += overflow;
                if (newVal[idx] > 9) {
                    overflow = 1;
                    newVal[idx] -= 10;
                } else {
                    overflow = 0;
                }
            } else {
                newVal.insert(newVal.begin(), 1);
                overflow = 0;
            }
            ++j;
        }
        BigNumber bn;
        bn.val_ = newVal;
        return bn;
    }
private:
    std::vector<char> val_;
};

std::ostream& operator<<(std::ostream& os, const BigNumber& n)
{
    return os << n.toString();
}

#define CHECK_SUM(n1_, n2_, sum_) { \
    BigNumber n1(n1_), n2(n2_), sum(sum_); \
    BigNumber n = n1 + n2; \
    if (n == sum) { \
        std::cerr << "passed " << n1 << " + " << n2 << " = " << n << std::endl; \
    } else { \
        std::cerr << "failed " << n1 << " + " << n2 << " : " << n << " != " << sum << std::endl; \
    } \
}

int main(int, char**)
{
    CHECK_SUM("12", "13", "25");
    CHECK_SUM("243290200817664", "3", "243290200817667");
    CHECK_SUM("243290200817664", "7", "243290200817671");
    CHECK_SUM("243290200817664", "37", "243290200817701");
    CHECK_SUM("243290200817664", "2969043922613559", "3212334123431223");
    return 0;
}
