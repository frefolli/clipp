#include <rf/clipp/utils.hh>
#include <regex>
#include <stdexcept>

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

std::string rf::clipp::toString(rf::clipp::Type type) {
    if (type == Void)
        return "void";
    if (type == String)
        return "string";
    if (type == Bool)
        return "bool";
    if (type == Int)
        return "int";
    return "undefined";
}

rf::clipp::HyperBool* rf::clipp::parseBool(std::string text) {
    if (std::regex_match(text, std::regex("[Tt][Rr][Uu][Ee]")))
        return new rf::clipp::HyperBool(true);
    if (std::regex_match(text, std::regex("[Ff][Aa][Ll][Ss][Ee]")))
        return new rf::clipp::HyperBool(false);
    return nullptr;
}

rf::clipp::HyperInt* rf::clipp::parseInt(std::string text) {
    if (std::regex_match(text, std::regex("[0-9]+")))
        return new rf::clipp::HyperInt(std::stoi(text));
    return nullptr;
}

rf::clipp::HyperObject* rf::clipp::parseObject(std::string text,
                                               rf::clipp::Type type) {
    if (type == String) {
        return new rf::clipp::HyperString(text);
    } else if (type == Bool) {
        return rf::clipp::parseBool(text);
    } else if (type == Int) {
        return rf::clipp::parseInt(text);
    }
    throw std::runtime_error("InvalidTypeException");
}
