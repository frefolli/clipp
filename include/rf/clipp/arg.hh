#ifndef RF_CLIPP_ARG
#define RF_CLIPP_ARG
#include <string>
namespace rf::clipp {
    class Arg {
        private:
            std::string name;
            bool optional;
            std::string help;
        public:
            Arg(std::string name,
                bool optional = false,
                std::string help = "");
            ~Arg();

            std::string getName();
            std::string getHelp();
            std::string getUsage();
            bool isOptional();
            HyperMap* process(int argc, char** args,
                              int& index, HyperMap* root);
    };
}
#endif
