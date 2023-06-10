#include <rf/clipp/menu.hh>
#include <rf/clipp/flag.hh>
#include <rf/clipp/arg.hh>
#include <rf/clipp/hypermap.hh>
#include <rf/clipp/hyperint.hh>
#include <rf/clipp/hyperbool.hh>
#include <rf/clipp/hyperstring.hh>
#include <iostream>
#include <stdexcept>

using namespace rf::clipp;

int ACTUAL_ARGC = 0;
char** ACTUAL_ARGS = nullptr;
char* FILE_NAME = nullptr;
void InitArgs(int argc, char** args) {
    FILE_NAME = args[0];
    ACTUAL_ARGC = argc+1;
    ACTUAL_ARGS = args-1;
}

Menu* InitMenu() {
    return new Menu { std::string(FILE_NAME), {
            new Menu("info", {}, { new Flag("verbose") }),
            new Menu("pull", {}, { new Flag("verbose") }),
            new Menu("push", {}, { new Flag("verbose") }),
        }, {
            new Flag("input"),
            new Flag("output file"),
            new Flag("format")
        }, {
            new Arg("width", false),
            new Arg("height", true)
        }
    };
}

HyperMap* ParseArgs(Menu* menu) {
    /*
    HyperMap* config = new HyperMap {{
        {"screen", new HyperMap {{
            {"width", new HyperInt(600)},
            {"height", new HyperInt(400)}
        }}},
        {"xterm", new HyperMap {{
            {"width", new HyperInt(80)},
            {"height", new HyperInt(60)}
        }}},
        {"check", new HyperString("FAIL")}
    }};
    return config;
    */
    return menu->process(ACTUAL_ARGC,
                         ACTUAL_ARGS);
}

void PrintUsage(Menu* menu) {
    std::cout << menu->getUsage() << std::endl;
}

void PrintConfig(HyperMap* config) {
    std::cout << config->toString() << std::endl;
}

/* TODO: DEV
template<class O, class ... I>
O* alloc(I... args) {
    if (O* ptr = new O {... args}; ptr != nullptr) {
        return ptr;
    } else {
        throw std::runtime_error("NullPointerException");
    }
}
*/

int main(int argc, char** args) {
    try {
        InitArgs(argc, args);
        if (Menu* menu = InitMenu(); menu != nullptr) {
            PrintUsage(menu);
            if (HyperMap* config = ParseArgs(menu); config != nullptr) {
                PrintConfig(config);
                delete config;
            }
            delete menu;
        }
        return 0;
    } catch(std::exception& error) {
        std::cerr << error.what() << std::endl;
        return 1;
    }
}
