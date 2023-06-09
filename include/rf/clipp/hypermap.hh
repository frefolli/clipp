#ifndef RF_CLIPP_HYPERMAP
#define RF_CLIPP_HYPERMAP
#include <rf/clipp/hyperobject.hh>
#include <string>
#include <map>
namespace rf::clipp {
    class HyperMap : public HyperObject {
        private:
            std::map<std::string, HyperObject*> data;
        public:
            HyperMap(std::map<std::string, HyperObject*> data = {});
            ~HyperMap();

            HyperObject* gets(std::string name);
            void sets(std::string name, HyperObject* ptr);

            template<class T>
            T& get(std::string name) {
                return *((T*) gets(name));
            }

            std::string toString();
            void* asPtr();
    };
}
#endif
