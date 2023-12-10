main: main.cpp Board.cpp Pebble.cpp computer.cpp
	g++ main.cpp Board.cpp Pebble.cpp computer.cpp -lmenu -o main -lsfml-graphics -lsfml-window -lsfml-system