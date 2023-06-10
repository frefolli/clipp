# Clipp

Command Line Interface Library of C++ inspired by `argpare.py`

## Build Guide

Hit `make` to build the library and the example executable `src/main.cc` with Meson.

## Recommended Usage

### Init Stuff

```c++
#include <rf/clipp/menu.hh>
#include <rf/clipp/flag.hh>
#include <rf/clipp/arg.hh>
#include <rf/clipp/type.hh>
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
    ACTUAL_ARGC = argc;
    ACTUAL_ARGS = args;
}
```

### Build your CLI

You can assemble a function to build the CLI like this:

```c++
Menu* InitMenu() {
    return new Menu { std::string(FILE_NAME), {
            new Menu("info", {}, { new Flag("verbose", Bool) }),
            new Menu("pull", {}, { new Flag("verbose") }),
            new Menu("push", {}, { new Flag("verbose") }),
        }, {
            new Flag("input", String),
            new Flag("output", String),
            new Flag("format", String),
            new Flag("help", Void)
        }, {
            new Arg("width", false, Int),
            new Arg("height", true, Int)
        }
    };
}
```

### Call the CLI

The with your main do something like this:

```c++
int main(int argc, char** args) {
    try {
        InitArgs(argc, args);
        if (Menu* menu = InitMenu(); menu != nullptr) {
            if (HyperMap* config = ParseArgs(menu); config != nullptr) {
                if (config->has("help"))
                    if (config->get<bool>("help"))
                        PrintUsage(menu);
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
```

### Some usefull stuff

```c++
HyperMap* ParseArgs(Menu* menu) {
    return menu->process(ACTUAL_ARGC,
                         ACTUAL_ARGS);
}

void PrintUsage(Menu* menu) {
    std::cout << menu->getUsage() << std::endl;
}

void PrintConfig(HyperMap* config) {
    std::cout << "config" << config->toString() << std::endl;
}
```

### Example Output

With `./build/main -h` the code prints the usage line and the JSON representation of config supplied with the CLI:

```text
./build/main [[info [-v]] | [pull [-v]] | [push [-v]]] [-i] [-o] [-f] [-h] width [height]
config{
        "help": true
}
```

An example of misusage is `./build/main 400 500x`:

```text
argument `height`, expected argument of type int, got "500x"
```
