#include <rf/clipp/flag.hh>
#include <stdexcept>
//  class Flag
//      std::string name
//      std::string longName
//      std::string shortName
//      std::string help
using namespace rf::clipp;

bool isLongName(std::string longName) {
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

bool isShortName(std::string shortName) {
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

std::string encodeLongName(std::string longName) {
    for (auto it = longName.begin(); it != longName.end(); ++it) {
        if (*it == ' ')
            *it = '-';
    }
    return longName;
}

Flag::Flag(std::string name,
     std::string longName,
     std::string shortName,
     std::string help) {
    if (longName.size() == 0)
        this->longName  = "--" + encodeLongName(name);
    else if (! isLongName(longName))
        throw std::runtime_error("invalid long name: " + longName);

    if (shortName.size() == 0)
        this->shortName  = "-" + name.substr(0, 1);
    else if (! isShortName(shortName))
        throw std::runtime_error("invalid short name: " + longName);
    
    this->help = help;
    this->name = name;
}

Flag::~Flag() {
    // NOP
}

std::string Flag::getName() {
    return name;
}

std::string Flag::getLongName() {
    return longName;
}

std::string Flag::getShortName() {
    return shortName;
}

std::string Flag::getHelp() {
    return help;
}

std::string Flag::getUsage() {
    return "[" + shortName + "]";
}

HyperMap* Flag::process(int argc, char** args, int& index, HyperMap* root) {
    HyperMap* config = new HyperMap();
    // ---- TODO ----
    // ---- TODO ----
    if (root == nullptr)
        return config;
    root->set(name, config);
    return root;
}
