#ifndef RF_CLIPP_ARG
#define RF_CLIPP_ARG
#include <string>
#include <rf/clipp/hypermap.hh>
#include <rf/clipp/type.hh>
namespace rf::clipp {
    class Arg {
        private:
            std::string name;
            bool optional;
            std::string help;
            Type type = Void;
        public:
            Arg(std::string name,
                bool optional = false,
                Type type = Void,
                std::string help = "");
            ~Arg();

            std::string getName();
            std::string getHelp();
            std::string getUsage();
            bool isOptional();
            
            bool process(int argc, char** args,
                         int& index, HyperMap*& root);
    };
}
#endif
