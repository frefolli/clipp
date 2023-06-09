#ifndef RF_CLIPP_HYPERSTRING
#define RF_CLIPP_HYPERSTRING
#include <rf/clipp/hyperobject.hh>
#include <string>
namespace rf::clipp {
    class HyperString : public HyperObject {
        private:
            std::string data;
        public:
            HyperString(std::string data);
            std::string toString();
            void* asPtr();
    };
}
#endif
