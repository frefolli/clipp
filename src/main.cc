#include <rf/clipp/menu.hh>
#include <rf/clipp/flag.hh>
#include <rf/clipp/arg.hh>
#include <iostream>
#include <stdexcept>

typedef rf::clipp::Menu Menu;
typedef rf::clipp::Flag Flag;
typedef rf::clipp::Arg Arg;

int main(int /*argc*/, char** args) {
    try {
        Menu* menu =
            new Menu { std::string(args[0]),
                {
                    new Menu("info", {}, {new Flag("verbose")}),
                    new Menu("pull", {}, {new Flag("verbose")}),
                    new Menu("push", {}, {new Flag("verbose")}),
                }, { new Flag("input"), new Flag("output file"), new Flag("format") },
                { new Arg("width", false), new Arg("height", true) }
            };
        std::cout << menu->getUsage() << std::endl;
        delete menu;
        return 0;
    } catch(std::exception& error) {
        std::cerr << error.what() << std::endl;
        return 1;
    }
}
