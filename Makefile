main: main.cpp Board.cpp Pebble.cpp computer.cpp button.cpp
	g++ main.cpp Board.cpp Pebble.cpp computer.cpp button.cpp -lmenu -o main -lsfml-graphics -lsfml-window -lsfml-system