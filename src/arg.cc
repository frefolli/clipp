#include <rf/clipp/arg.hh>
#include <stdexcept>
#include <rf/clipp/hyperstring.hh>
#include <rf/clipp/utils.hh>
//  class Arg
//      std::string name
//      bool optional
//      std::string help

using namespace rf::clipp;

Arg::Arg(std::string name,
         bool optional,
         Type type,
         std::string help) {
    this->name = name;
    this->optional = optional;
    this->help = help;
    this->type = type;
}

Arg::~Arg() {
    // NOP
}

std::string Arg::getName() {
    return name;
}

std::string Arg::getHelp() {
    return help;
}

std::string Arg::getUsage() {
    if (optional)
        return "[" + name + "]";
    return name;
}

bool Arg::isOptional() {
    return optional;
}

bool Arg::process(int argc, char** args, int& index, HyperMap*& root) {
    if (index >= argc)
        return false;
    
    if (root == nullptr)
        throw std::runtime_error("NullPointerException");
    
    if (root->has(name))
        return false;

    if (index >= argc) {
        throw std::runtime_error("argument `" + name +
                                 "`, expected argument of type " +
                                 toString(type));
    }
    if (HyperObject* obj = parseObject(args[index], type);
        obj != nullptr) {
        root->sets(name, obj);
        ++index;
    } else {
        // TODO: support default value
        throw std::runtime_error("argument `" + name +
                                 "`, expected argument of type " +
                                 toString(type) + ", got \"" +
                                 args[index] + "\"");
    }
    
    return true;
}
