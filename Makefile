DEBUG=
CMAKE_FLAGS=-DGLFW_BUILD_DOCS=0
ifdef DEBUG
	CMAKE_FLAGS+=-DCMAKE_BUILD_TYPE=Debug
endif

all: build compile

run:
	build/bin/base

build:
	mkdir -p build
	cmake3 -B build . $(CMAKE_FLAGS)

compile:
	make -C build

clean:
	rm -r build

.PHONY: all build compile clean
