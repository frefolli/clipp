#include <rf/clipp/utils.hh>
#include <regex>
std::string rf::clipp::indentString(std::string str) {
    return std::regex_replace(str, std::regex("\\n"), "\n\t");
}

bool rf::clipp::isLongName(std::string longName) {
    if (longName.size() <= 2)
        return false;
    if (longName.substr(0, 2) != "--")
        return false;
    for (auto it = longName.begin()+2; it != longName.end(); ++it) {
        char c = *it;
        if (! ((c == '-') ||
               ((c >= '0' ) && (c <= '9')) ||
               ((c >= 'A' ) && (c <= 'Z')) ||
               ((c >= 'a' ) && (c <= 'z'))))
            return false;
    }
    return true;
}

bool rf::clipp::isShortName(std::string shortName) {
    if (shortName.size() != 2)
        return false;
    if (shortName[0] != '-')
        return false;
    char c = shortName[1];
    if (! ((c == '-') ||
           ((c >= '0' ) && (c <= '9')) ||
           ((c >= 'A' ) && (c <= 'Z')) ||
           ((c >= 'a' ) && (c <= 'z'))))
        return false;
    return true;
}

std::string rf::clipp::encodeLongName(std::string longName) {
    for (auto it = longName.begin(); it != longName.end(); ++it) {
        if (*it == ' ')
            *it = '-';
    }
    return longName;
}
