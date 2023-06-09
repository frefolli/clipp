#include <rf/clipp/hypermap.hh>
#include <stdexcept>
#include <regex>
//  class Hypermap
//      std::map<std::string, HyperObject*> data
using namespace rf::clipp;

HyperMap::HyperMap(std::map<std::string, HyperObject*> data) {
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (it->second == nullptr)
            throw std::runtime_error("NullPointerException");
    }
    this->data = data;
}

HyperMap::~HyperMap() {
    for (auto it = data.begin(); it != data.end(); ++it)
        if (it->second != nullptr)
            delete it->second;
}

HyperObject* HyperMap::gets(std::string name) {
    auto it = data.find(name);
    if (it == data.end())
        return nullptr;
    return it->second;
}

void HyperMap::sets(std::string name, HyperObject* ptr) {
    if (ptr == nullptr)
        throw std::runtime_error("NullPointerException");
    auto it = data.find(name);
    if (it != data.end())
        delete data[name];
    data[name] = ptr;
}

std::string indentString(std::string str) {
    return std::regex_replace(str, std::regex("\\n"), "\n\t");
}

std::string HyperMap::toString() {
    if (data.size() == 0)
        return "{}";
    std::string rep = "{";
    for (auto it = data.begin(); it != data.end();) {
        rep += indentString("\n\"" + it->first + "\": " +
                            it->second->toString());
        ++it;
        if (it != data.end())
            rep += ",";
    }
    return rep + "\n}";
}

void* HyperMap::asPtr() {
    return nullptr;
};
