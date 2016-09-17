CFLAGS = -std=c++11 -w -fno-stack-protector # disable canaries

bin/main: bin/main.o bin/menu.o bin/game.o bin/InfoPanel.o bin/Player.o bin/Actor.o
	g++ -g bin/main.o bin/menu.o bin/game.o bin/InfoPanel.o  bin/Actor.o bin/Player.o -o bin/main $(CFLAGS) -lncurses

bin/main.o: src/main.cpp
	g++ -g -c -o bin/main.o src/main.cpp $(CFLAGS)

bin/menu.o: src/menu.cpp src/menu.h src/game.h src/InfoPanel.h
	g++ -g -c -o bin/menu.o src/menu.cpp $(CFLAGS)

bin/game.o: src/game.cpp src/game.h src/menu.h src/InfoPanel.h src/Player.h src/Actor.h
	g++ -g -c -o bin/game.o src/game.cpp $(CFLAGS)

bin/InfoPanel.o: src/InfoPanel.cpp src/InfoPanel.h
	g++ -g -c -o bin/InfoPanel.o src/InfoPanel.cpp $(CFLAGS)

bin/Actor.o: src/Actor.cpp src/Actor.h
	g++ -g -c -o bin/Actor.o src/Actor.cpp $(CFLAGS)

bin/Player.o: src/Player.cpp src/Player.h bin/Actor.o
	g++ -g -c -o bin/Player.o src/Player.cpp $(CFLAGS)

