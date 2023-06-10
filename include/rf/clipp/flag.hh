#ifndef RF_CLIPP_FLAG
#define RF_CLIPP_FLAG
#include <string>
#include <rf/clipp/hypermap.hh>
#include <rf/clipp/type.hh>
namespace rf::clipp {
    class Flag {
        private:
            std::string name;
            std::string longName;
            std::string shortName;
            std::string help;
            Type type = Void;
        public:
            Flag(std::string name,
                 Type type = Void,
                 std::string longName = "",
                 std::string shortName = "",
                 std::string help = "");
            ~Flag();

            std::string getName();
            std::string getLongName();
            std::string getShortName();
            std::string getHelp();
            std::string getUsage();
            bool process(int argc, char** args,
                         int& index, HyperMap*& root);
    };
}
#endif
