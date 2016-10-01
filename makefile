CFLAGS = -std=c++11 -w -Wall -fno-stack-protector # disable canaries

termq: build/main.o build/menu.o build/game.o build/Actor.o build/Player.o build/Enemy.o build/Item.o build/Coin.o build/Global.o
	g++ -g src/*.cpp src/classes/*.cpp src/global/Global.cpp -o bin/termq $(CFLAGS) -lncurses

build/main.o: src/main.cpp
	g++ -g -c -o build/main.o src/main.cpp $(CFLAGS)

build/Global.o: src/global/Global.cpp src/global/Global.h
	g++ -g -c -o build/Global.o src/global/Global.cpp $(CFLAGS)

build/menu.o: src/menu.cpp src/menu.h
	g++ -g -c -o build/menu.o src/menu.cpp $(CFLAGS)

build/game.o: src/game.cpp src/game.h src/menu.h
	g++ -g -c -o build/game.o src/game.cpp $(CFLAGS)

build/Window.o: src/classes/Window.cpp src/classes/Window.h
	g++ -g -c -o build/Window.o src/classes/Window.cpp $(CFLAGS)

build/DiagWindow.o: src/classes/DiagWindow.cpp src/classes/DiagWindow.h build/Window.o
	g++ -g -c -o build/DiagWindow.o src/classes/DiagWindow.cpp $(CFLAGS)

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
