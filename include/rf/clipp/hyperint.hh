#ifndef RF_CLIPP_HYPERINT
#define RF_CLIPP_HYPERINT
#include <rf/clipp/hyperobject.hh>
#include <string>
namespace rf::clipp {
    class HyperInt : public HyperObject {
        private:
            int data;
        public:
            HyperInt(int data);
            std::string toString();
            void* asPtr();
    };
}
#endif
