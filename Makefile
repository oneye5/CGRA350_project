DEBUG=
CMAKE_FLAGS=
ifdef DEBUG
	CMAKE_FLAGS+=-DCMAKE_BUILD_TYPE=Debug
endif

all: build compile

run:
	build/bin/base

build:
	mkdir -p build
	cmake3 -B build . -G Ninja $(CMAKE_FLAGS)

compile:
	ninja -C build

clean:
	rm -r build

.PHONY: all build compile clean
