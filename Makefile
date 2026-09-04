.PHONY: run build test clean gdb valgrind asan

build:
	meson setup build --reconfigure 2>/dev/null || meson setup build
	ninja -C build

run: build
	./build/raylib-boilerplate

test:
	./build/test_runner

clean:
	rm -rf build build-asan

gdb: build
	gdb ./build/raylib-boilerplate

valgrind: build
	valgrind --leak-check=full --suppressions=valgrind.suppress --track-origins=yes ./build/raylib-boilerplate

asan:
	meson setup build-asan --buildtype=debug -Db_sanitize=address 2>/dev/null || true
	ninja -C build-asan
	./build-asan/raylib-boilerplate

.DEFAULT_GOAL = run
