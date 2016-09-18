CFLAGS = -std=c++11 -w -fno-stack-protector # disable canaries

bin/main: build/main.o build/menu.o build/game.o build/InfoPanel.o build/Actor.o build/Player.o build/Enemy.o
	g++ -g build/main.o build/menu.o build/game.o build/InfoPanel.o  build/Actor.o build/Player.o build/Enemy.o -o bin/main $(CFLAGS) -lncurses

build/main.o: src/main.cpp
	g++ -g -c -o build/main.o src/main.cpp $(CFLAGS)

build/menu.o: src/menu.cpp src/menu.h src/game.h src/classes/InfoPanel.h
	g++ -g -c -o build/menu.o src/menu.cpp $(CFLAGS)

build/game.o: src/game.cpp src/game.h src/menu.h src/classes/InfoPanel.h src/classes/Actor.h src/classes/Player.h src/classes/Enemy.h
	g++ -g -c -o build/game.o src/game.cpp $(CFLAGS)

build/InfoPanel.o: src/classes/InfoPanel.cpp src/classes/InfoPanel.h
	g++ -g -c -o build/InfoPanel.o src/classes/InfoPanel.cpp $(CFLAGS)

build/Actor.o: src/classes/Actor.cpp src/classes/Actor.h
	g++ -g -c -o build/Actor.o src/classes/Actor.cpp $(CFLAGS)

build/Player.o: src/classes/Player.cpp src/classes/Player.h build/Actor.o
	g++ -g -c -o build/Player.o src/classes/Player.cpp $(CFLAGS)

build/Enemy.o: src/classes/Enemy.cpp src/classes/Enemy.h build/Actor.o
	g++ -g -c -o build/Enemy.o src/classes/Enemy.cpp $(CFLAGS)

clean:
	rm -f build/*
