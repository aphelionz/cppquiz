.PHONY = build-all
build-all:
	cmake -S . -B build
	cmake --build build
	
clean:
	rm -rf build


# For a single-configuration generator:
# $ cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
# $ cmake --build build
# $ cmake --install build --prefix /path/to/wherever

# For a multi-configuration generator:
# $ cmake -S . -B build
# $ cmake --build build --config Release
# $ cmake --install build --config Release --prefix /path/to/wherever
