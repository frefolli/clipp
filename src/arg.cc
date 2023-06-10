#include <rf/clipp/arg.hh>
#include <stdexcept>
#include <rf/clipp/hyperstring.hh>
//  class Arg
//      std::string name
//      bool optional
//      std::string help

using namespace rf::clipp;

Arg::Arg(std::string name,
         bool optional,
         std::string help) {
    this->name = name;
    this->optional = optional;
    this->help = help;
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
    // ---- TODO ----
    if (root == nullptr)
        throw std::runtime_error("NullPointerException");
    if (root->has(name))
        return false;
    root->sets(name, new HyperString(args[index]));
    ++index;
    // ---- TODO ----
    return true;
}
