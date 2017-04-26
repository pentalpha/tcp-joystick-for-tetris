#!/bin/sh

if [ "$1" = "DBG" ]
then
	export CPP_FLAGS=" -Wall -Wextra -g -std=c++11  "
	export LINK_FLAGS=" -lcurses -pthread"
	./util/build.sh $(cat version.txt)
else
if [ "$1" = "REL" ]
then
	export CPP_FLAGS=" -Wall -Wextra -O2 -std=c++11 "
	export LINK_FLAGS=" -static-libgcc -static-libstdc++ -lcurses -pthread"
	./util/build_arm.sh $(cat version.txt)
else
	echo "please invoke with arg \"DBG\" or \"REL\""
	exit 1
fi
fi
