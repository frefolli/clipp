@all: ./build/main

./build/main: include/rf/clipp/*.hh src/*.cc
	meson build
	meson compile -C build

run: ./build/main
	./build/main

clean:
	rm -rf build
