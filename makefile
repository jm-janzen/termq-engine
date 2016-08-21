CFLAGS = -std=c++11 -w -fno-stack-protector # disable canaries

bin/main: bin/main.o bin/game.o bin/Winfo.o
	g++ -g -o bin/main bin/main.o bin/game.o bin/Winfo.o $(CFLAGS) -lncurses

bin/main.o: src/main.cpp
	g++ -g -c -o bin/main.o src/main.cpp $(CFLAGS)

bin/game.o: src/game.cpp src/game.h src/Winfo.h
	g++ -g -c -o bin/game.o src/game.cpp $(CFLAGS)

bin/Winfo.o: src/Winfo.cpp src/Winfo.h
	g++ -g -c -o bin/Winfo.o src/Winfo.cpp $(CFLAGS)

