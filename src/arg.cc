#include <rf/clipp/arg.hh>
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

HyperMap* Arg::process(int argc, char** args, int& index, HyperMap* root) {
    HyperMap* config = new HyperMap();
    // ---- TODO ----
    // ---- TODO ----
    if (root == nullptr)
        return config;
    root->set(name, config);
    return root;
}
