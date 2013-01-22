#!/bin/sh
if [ -d target ]; then
	rm -rf target
fi
if [ -f ori.log ]; then
	rm -f ori.log
fi
if [ -f ori.log.back ]; then
	rm -f ori.log.back
fi

