.PHONY: run build
run: build
	./build/flies

build:
	clear
	cmake . -B build
	make -C build
