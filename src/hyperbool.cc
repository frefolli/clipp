#include <rf/clipp/hyperbool.hh>
//  class HyperBool
//      bool data
using namespace rf::clipp;

HyperBool::HyperBool(bool data) {
    this->data = data;
}

std::string HyperBool::toString() {
    if (data)
        return "true";
    return "false";
}

void* HyperBool::asPtr() {
    return (void*) (&data);
}
