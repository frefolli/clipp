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
    auto it = data.find(name);
    if (it != data.end())
        delete it->second;
    data[name] = ptr;
}

std::string indentString(std::string str) {
    for (auto it = str.begin(); it != str.end(); ++it) {
        if (*it == '\n') {
            str.replace(it, it+1, "\n\t");
        }
    }
    return "\n" + str;
}

std::string toString(void* ptr) {
    std::string objStr = "undefined";
    if (std::string* obj = dynamic_cast<std::string*>(ptr);
            obj != nullptr) {
        objStr = *obj;
    } else if (HyperMap* obj = dynamic_cast<HyperMap*>(ptr);
            obj != nullptr) {
        objStr = obj->toString();
    } else if (bool* obj = dynamic_cast<bool*>(ptr);
            obj != nullptr) {
        objStr = (*obj) ? "true" : "false";
    } else if (int* obj = dynamic_cast<int*>(ptr);
            obj != nullptr) {
        objStr = std::to_string(*obj);
    }
    return objStr;
}

std::string HyperMap::toString() {
    if (data.size() == 0)
        return "{}";
    std::string rep = "{";
    for (auto it = data.begin(); it != data.end(); ++it) {
        rep += "\n" + indentString("\"" + it->first + "\": " +
                                   toString(it->second));
    }
    return rep + "\n}";
}
