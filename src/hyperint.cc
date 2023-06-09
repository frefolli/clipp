#include <rf/clipp/hyperint.hh>
//  class HyperInt
//      int data
using namespace rf::clipp;

HyperInt::HyperInt(int data) {
    this->data = data;
}

std::string HyperInt::toString() {
    return std::to_string(data);
}

void* HyperInt::asPtr() {
    return (void*) (&data);
}
