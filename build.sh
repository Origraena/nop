#!/bin/sh
if [ ! -d target/build ]; then
	mkdir -p target/build
fi
if [ ! -d target/release ]; then
	mkdir -p target/release
fi
g++ -o target/release/nop -Ilib/includes -Llib/bin -linterceptor src/*.cpp src/event/*.cpp 
