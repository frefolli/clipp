#ifndef RF_CLIPP_UTILS
#define RF_CLIPP_UTILS
#include <string>
#include <rf/clipp/type.hh>
#include <rf/clipp/hyperbool.hh>
#include <rf/clipp/hyperstring.hh>
#include <rf/clipp/hyperint.hh>
namespace rf::clipp {
    std::string indentString(std::string str);
    bool isLongName(std::string longName);
    bool isShortName(std::string shortName);
    std::string encodeLongName(std::string longName);
    std::string toString(Type type);
    HyperBool* parseBool(std::string text);
    HyperInt* parseInt(std::string text);
    HyperObject* parseObject(std::string text, Type type);
}
#endif
