#ifndef RF_CLIPP_HYPERMAP
#define RF_CLIPP_HYPERMAP
#include <string>
#include <map>
namespace rf::clipp {
    class HyperMap {
        private:
            std::map<std::string, void*> data;
        public:
            HyperMap(std::map<std::string, void*> data = {});
            ~HyperMap();

            void* gets(std::string name);
            void sets(std::string name, void* ptr);
            
            template<class T>
            void set(std::string name, T* ptr) {
                sets(name, (void*) ptr);
            }

            template<class T>
            T& get(std::string name) {
                return *((T*) gets(name));
            }
    };
}
#endif
