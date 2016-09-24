CFLAGS = -std=c++11 -w -Wall -fno-stack-protector # disable canaries

termq: build/main.o build/menu.o build/game.o build/InfoPanel.o build/Actor.o build/Player.o build/Enemy.o build/Item.o build/Coin.o
	g++ -g src/*.cpp src/classes/*.cpp -o bin/termq $(CFLAGS) -lncurses -g

build/main.o: src/main.cpp
	g++ -g -c -o build/main.o src/main.cpp $(CFLAGS)

build/menu.o: src/menu.cpp src/menu.h src/classes/InfoPanel.h
	g++ -g -c -o build/menu.o src/menu.cpp $(CFLAGS)

build/game.o: src/game.cpp src/game.h src/menu.h src/classes/InfoPanel.h
	g++ -g -c -o build/game.o src/game.cpp $(CFLAGS)

build/Window.o: src/classes/Window.cpp src/classes/Window.h
	g++ -g -c -o build/Window.o src/classes/Window.cpp $(CFLAGS)

build/InfoPanel.o: src/classes/InfoPanel.cpp src/classes/InfoPanel.h
	g++ -g -c -o build/InfoPanel.o src/classes/InfoPanel.cpp $(CFLAGS)

build/Actor.o: src/classes/Actor.cpp src/classes/Actor.h
	g++ -g -c -o build/Actor.o src/classes/Actor.cpp $(CFLAGS)

build/Player.o: src/classes/Player.cpp src/classes/Player.h build/Actor.o
	g++ -g -c -o build/Player.o src/classes/Player.cpp $(CFLAGS)

build/Enemy.o: src/classes/Enemy.cpp src/classes/Enemy.h build/Actor.o
	g++ -g -c -o build/Enemy.o src/classes/Enemy.cpp $(CFLAGS)

build/Item.o: src/classes/Item.cpp src/classes/Item.h
	g++ -g -c -o build/Item.o src/classes/Item.cpp $(CFLAGS)

build/Coin.o: src/classes/Coin.cpp src/classes/Coin.h build/Item.o
	g++ -g -c -o build/Coin.o src/classes/Coin.cpp $(CFLAGS)

clean:
	rm -f build/* bin/*
