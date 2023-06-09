#ifndef RF_CLIPP_HYPEROBJECT
#define RF_CLIPP_HYPEROBJECT
#include <string>

namespace rf::clipp {
    class HyperObject {
        public:
            virtual ~HyperObject();
            virtual std::string toString() = 0;
            virtual void* asPtr() = 0;
    };
}
#endif
