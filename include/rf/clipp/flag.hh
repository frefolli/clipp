#ifndef RF_CLIPP_FLAG
#define RF_CLIPP_FLAG
#include <string>
namespace rf::clipp {
    class Flag {
        private:
            std::string name;
            std::string longName;
            std::string shortName;
            std::string help;
        public:
            Flag(std::string name,
                 std::string longName = "",
                 std::string shortName = "",
                 std::string help = "");
            ~Flag();

            std::string getName();
            std::string getLongName();
            std::string getShortName();
            std::string getHelp();
            std::string getUsage();
            HyperMap* process(int argc, char** args,
                              int& index, HyperMap* root);
    };
}
#endif
