#ifndef RF_CLIPP_MENU
#define RF_CLIPP_MENU
#include <rf/clipp/arg.hh>
#include <rf/clipp/flag.hh>
#include <rf/clipp/hypermap.hh>
#include <vector>
namespace rf::clipp {
    class Menu {
        private:
            std::string name;
            std::vector<Menu*> subMenus;
            std::vector<Flag*> flags;
            std::vector<Arg*> args;
        public:
            Menu(std::string name = "",
                 std::vector<Menu*> subMenus = {},
                 std::vector<Flag*> flags = {},
                 std::vector<Arg*> args = {});
            ~Menu();
            std::string getUsage();
            std::string getHelp();
            std::string getName();

            HyperMap* process(int argc, char** args,
                              HyperMap* config = nullptr);
    };
}
#endif
