CFLAGS = -std=c++11 -w -fno-stack-protector # disable canaries

bin/main: bin/main.o bin/game.o bin/InfoPanel.o
	g++ -g -o bin/main bin/main.o bin/game.o bin/InfoPanel.o $(CFLAGS) -lncurses

bin/main.o: src/main.cpp
	g++ -g -c -o bin/main.o src/main.cpp $(CFLAGS)

bin/game.o: src/game.cpp src/game.h src/InfoPanel.h
	g++ -g -c -o bin/game.o src/game.cpp $(CFLAGS)

bin/InfoPanel.o: src/InfoPanel.cpp src/InfoPanel.h
	g++ -g -c -o bin/InfoPanel.o src/InfoPanel.cpp $(CFLAGS)

