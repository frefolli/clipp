#include <rf/clipp/hyperstring.hh>
//  class HyperString
//      std::string data
using namespace rf::clipp;

HyperString::HyperString(std::string data) {
    this->data = data;
}

std::string HyperString::toString() {
    return data;
}

void* HyperString::asPtr() {
    return (void*) (&data);
}
