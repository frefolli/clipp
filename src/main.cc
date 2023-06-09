#include <rf/clipp/menu.hh>
#include <rf/clipp/flag.hh>
#include <rf/clipp/arg.hh>
#include <iostream>
#include <stdexcept>

typedef rf::clipp::Menu Menu;
typedef rf::clipp::Flag Flag;
typedef rf::clipp::Arg Arg;
typedef rf::clipp::HyperMap HyperMap;

int ACTUAL_ARGC = 0;
char** ACTUAL_ARGS = nullptr;
char* FILE_NAME = nullptr;
void InitArgs(int argc, char** args) {
    FILE_NAME = args[0];
    ACTUAL_ARGC = argc+1;
    ACTUAL_ARGS = args-1;
}

Menu* InitMenu() {
    return new Menu { std::string(FILE_NAME, {
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
    HyperMap* config = new HyperMap {{
        {"screen", new HyperMap {{
            {"width", new int(600)},
            {"height", new int(400)}
        }}},
        {"xterm", new HyperMap {{
            {"width", new int(80)},
            {"height", new int(60)}
        }}},
        {"check", new std::string("FAIL")}
    }};
    return menu->parseArgs(ACTUAL_ARGC,
                           ACTUAL_ARGS,
                           config);
}

void PrintUsage(Menu* menu) {
    std::cout << MENU->getUsage() << std::endl;
}

void PrintConfig(HyperMap* config) {
    std::cout << config->toString() << std::endl;
}

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
