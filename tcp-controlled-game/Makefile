all:
	g++ \
	src/NetworkController/Queue.cpp \
	src/NetworkController/StringQueue.cpp \
	src/NetworkController/Server.cpp \
	src/NetworkController/NetworkController.cpp \
	src/figures.cpp \
	src/game.cpp \
	src/Iscreen.cpp \
	src/main.cpp \
	src/main_menu.cpp \
	src/terminal.cpp \
	src/util/char_data.cpp \
	-o bin/tetris-on-terminal -lcurses -pthread -Wall -Wextra -O2 -std=c++11

arm:
	arm-linux-gnueabihf-g++ \
	src/NetworkController/NetworkController.cpp \
	src/NetworkController/gpio.cpp \
	src/NetworkController/Queue.cpp \
	src/NetworkController/run.cpp \
	src/figures.cpp \
	src/game.cpp \
	src/Iscreen.cpp \
	src/main.cpp \
	src/main_menu.cpp \
	src/terminal.cpp \
	src/util/char_data.cpp \
	-o bin/tetris-on-terminal_arm -static-libgcc -static-libstdc++ -lcurses -pthread -Wall -Wextra -O2 -std=c++11
