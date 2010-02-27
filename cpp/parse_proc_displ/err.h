#ifndef ERR_H
#define ERR_H

#include <string>

enum ReturnCode {
    SUCCESS = 0,
    FAILURE = -1,
    SKIP = -2
};

void setLastErrorText(const std::string& str);
std::string getLastErrorText();


#endif /* ERR_H */

