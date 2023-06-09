#include <rf/clipp/menu.hh>
#include <rf/clipp/hyperstring.hh>
#include <stdexcept>
//  class Menu
//      std::string name
//      std::vector<Menu*> subMenus
//      std::vector<Flag*> flags
//      std::vector<Arg*> args

using namespace rf::clipp;

Menu::Menu(std::string name,
           std::vector<Menu*> subMenus,
           std::vector<Flag*> flags,
           std::vector<Arg*> args) {
    for (auto it = subMenus.begin(); it != subMenus.end(); ++it)
        if (*it == nullptr)
            throw std::runtime_error("NullPointerException");
    for (auto it = flags.begin(); it != flags.end(); ++it)
        if (*it == nullptr)
            throw std::runtime_error("NullPointerException");
    for (auto it = args.begin(); it != args.end(); ++it)
        if (*it == nullptr)
            throw std::runtime_error("NullPointerException");
    this->subMenus = subMenus;
    this->flags = flags;
    this->args = args;
    this->name = name;
}

Menu::~Menu() {
    for (auto it = subMenus.begin(); it != subMenus.end(); ++it)
        if (*it != nullptr)
            delete *it;
    for (auto it = flags.begin(); it != flags.end(); ++it)
        if (*it != nullptr)
            delete *it;
    for (auto it = args.begin(); it != args.end(); ++it)
        if (*it != nullptr)
            delete *it;
}

std::string Menu::getUsage() {
    std::string rep = name;
    
    if (subMenus.size() > 0)
        rep += " [";
    for (auto it = subMenus.begin(); it != subMenus.end(); ++it)
        if (*it != nullptr) {
            if (it == subMenus.begin()) {
                rep += "[" + (*it)->getUsage() + "]";
            } else {
                rep += " | [" + (*it)->getUsage() + "]";
            }
        }
    if (subMenus.size() > 0)
        rep += "]";

    for (auto it = flags.begin(); it != flags.end(); ++it)
        if (*it != nullptr)
            rep += " " + (*it)->getUsage();
    
    for (auto it = args.begin(); it != args.end(); ++it)
        if (*it != nullptr)
            rep += " " + (*it)->getUsage();
    
    return rep;
}

std::string Menu::getHelp() {
    throw std::runtime_error("NotImplementedException");
}

std::string Menu::getName() {
    return name;
}

HyperMap* Menu::process(int argc, char** args,
                        HyperMap* config) {
    if (config == nullptr) {
        config = new HyperMap();
    }
    // ---- TODO ----
    config->sets("check", new HyperString("OK"));
    // ---- TODO ----
    return config;
}
