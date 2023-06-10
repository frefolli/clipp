#include <rf/clipp/flag.hh>
#include <stdexcept>
#include <rf/clipp/hyperbool.hh>
#include <cstring>
#include <rf/clipp/utils.hh>
//  class Flag
//      std::string name
//      std::string longName
//      std::string shortName
//      std::string help
using namespace rf::clipp;

Flag::Flag(std::string name,
           Type type,
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
    this->type = type;
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

bool Flag::process(int argc, char** args, int& index, HyperMap*& root) {
    if (index >= argc)
        throw std::runtime_error("InvalidIndexException");
    if ((std::strcmp(shortName.c_str(), args[index]) != 0) &&
        (std::strcmp(longName.c_str(), args[index]) != 0)) {
        return false;
    }; ++index;
    if (root == nullptr)
        throw std::runtime_error("NullPointerException");
   
    if (type == Void) {
        root->sets(name, new HyperBool(true));
    } else {
        if (index >= argc) {
            throw std::runtime_error("flag `" + name +
                                     "`, expected argument of type " +
                                     toString(type));
        }
        if (HyperObject* obj = parseObject(args[index], type);
            obj != nullptr) {
            root->sets(name, obj);
            ++index;
        } else {
            // TODO: support default value
            throw std::runtime_error("flag `" + name +
                                     "`, expected argument of type " +
                                     toString(type) + ", got \"" +
                                     args[index] + "\"");
        }
    }

    return true;
}
