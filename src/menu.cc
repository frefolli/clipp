#include <rf/clipp/menu.hh>
#include <rf/clipp/hyperstring.hh>
#include <cstring>
#include <stdexcept>
#include <iostream>
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

bool Menu::process(int argc, char** args, int& index, HyperMap*& root) {
    if (index >= argc)
        throw std::runtime_error("InvalidIndexException");
    
    if (std::strcmp(name.c_str(), args[index]) != 0) {
        return false;
    }; ++index;
    HyperMap* config = new HyperMap();

    while (index < argc) {
        bool foundSomething = false;
        // SUB MENUS
        for (auto it = subMenus.begin(); it != subMenus.end(); ++it) {
            foundSomething |= (*it)->process(argc, args, index, config);
            if (foundSomething) break;
        }; if (foundSomething) continue;

        // FLAGS
        for (auto it = flags.begin(); it != flags.end(); ++it) {
            foundSomething |= (*it)->process(argc, args, index, config);
            if (foundSomething) break;
        }; if (foundSomething) continue;

        // 
        for (auto it = this->args.begin(); it != this->args.end(); ++it) {
            foundSomething |= (*it)->process(argc, args, index, config);
            if (foundSomething) break;
        }; if (foundSomething) continue;

        if (!foundSomething)
            break;
    }

    if (root == nullptr) {
        root = config;
    } else {
        root->sets(name, config);
    }
    return true;
}

HyperMap* Menu::process(int argc, char** args) {
    int index = 0;
    if (index >= argc)
        return new HyperMap();
    HyperMap* root = nullptr;
    process(argc, args, index, root);
    return root;
}
