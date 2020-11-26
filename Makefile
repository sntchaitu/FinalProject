game:
	g++  -I/Graphics/*.cpp -I/Shapes/*.cpp -I/Scenes/*.cpp -I/Input/*.cpp  -I/Games/*.cpp -I/Breakout/*.cpp -I/App/*.cpp main.cpp -o play -I include -L lib -l SDL2-2.0.0