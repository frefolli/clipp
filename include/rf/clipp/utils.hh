#ifndef RF_CLIPP_UTILS
#define RF_CLIPP_UTILS
#include <string>
namespace rf::clipp {
    std::string indentString(std::string str);
    bool isLongName(std::string longName);
    bool isShortName(std::string shortName);
    std::string encodeLongName(std::string longName);
}
#endif
