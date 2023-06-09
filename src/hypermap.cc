#include <rf/clipp/hypermap.hh>
#include <stdexcept>
//  class Hypermap
//      std::map<std::string, void*> data

using namespace rf::clipp;

HyperMap::HyperMap(std::map<std::string, void*> data) {
    for (auto it = data.begin(); it != data.end(); ++it)
        if (it->second == nullptr)
            throw std::runtime_error("NullPointerException");
    data = data;
}

HyperMap::~HyperMap() {
    for (auto it = data.begin(); it != data.end(); ++it)
        if (it->second != nullptr)
            delete it->second;
}

void* HyperMap::gets(std::string name) {
    auto it = data.find(name);
    if (it == data.end())
        return nullptr;
    return it->second;
}

void HyperMap::sets(std::string name, void* ptr) {
    if (ptr == nullptr)
        throw std::runtime_error("NullPointerException");
}
