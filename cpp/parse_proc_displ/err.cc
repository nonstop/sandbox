#include "err.h"

static std::string errText;
void setLastErrorText(const std::string& str)
{
    errText = str;
}

std::string getLastErrorText()
{
    return errText;
}
