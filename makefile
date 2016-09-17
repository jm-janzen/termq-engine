CFLAGS = -std=c++11 -w -fno-stack-protector # disable canaries

bin/main: bin/main.o bin/menu.o bin/game.o bin/InfoPanel.o bin/Player.o
	g++ -g -o bin/main bin/main.o bin/menu.o bin/game.o bin/InfoPanel.o  bin/Player.o $(CFLAGS) -lncurses

bin/main.o: src/main.cpp
	g++ -g -c -o bin/main.o src/main.cpp $(CFLAGS)

bin/menu.o: src/menu.cpp src/menu.h src/game.h src/InfoPanel.h
	g++ -g -c -o bin/menu.o src/menu.cpp $(CFLAGS)

bin/game.o: src/game.cpp src/game.h src/menu.h src/InfoPanel.h src/Player.h
	g++ -g -c -o bin/game.o src/game.cpp $(CFLAGS)

bin/InfoPanel.o: src/InfoPanel.cpp src/InfoPanel.h
	g++ -g -c -o bin/InfoPanel.o src/InfoPanel.cpp $(CFLAGS)

bin/Player.o: src/Player.cpp src/Player.h
	g++ -g -c -o bin/Player.o src/Player.cpp $(CFLAGS)

