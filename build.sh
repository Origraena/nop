#!/bin/sh
if [ ! -d target/build ]; then
	mkdir -p target/build
fi
if [ ! -d target/release ]; then
	mkdir -p target/release
fi
gcc -c src/main.c -o target/build/main.o -Ilib/includes
gcc -o target/release/nhp target/build/*.o -Llib/bin -linterceptor
