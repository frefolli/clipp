#ifndef RF_CLIPP_HYPERBOOL
#define RF_CLIPP_HYPERBOOL
#include <rf/clipp/hyperobject.hh>
#include <string>
namespace rf::clipp {
    class HyperBool : public HyperObject {
        private:
            bool data;
        public:
            HyperBool(bool data);
            std::string toString();
            void* asPtr();
    };
}
#endif
