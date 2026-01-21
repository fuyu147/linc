.PHONY: run build
run: build
	./build/linc

build:
	clear
	cmake . -B build
	make -C build
